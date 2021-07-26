//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/product_type.hpp>
#include <eve/function/is_equal.hpp>
#include <type_traits>

namespace udt
{
  //------------------------------------------------------------------------------------------------
  // This test UDT is made to be a placeholder for the worst case scenario where nothing can be
  // added to the type we want to adapt. In practice, yes, we'll instruct people on using proper
  // friend function, make get wrappers, etc... but this protocol must work in all cases, so no
  // cheating.
  //------------------------------------------------------------------------------------------------
  struct grid2d
  {
    int x = +1, y = -1;
    friend constexpr auto operator<=>(grid2d,grid2d) = default;

    static int eq_counter, neq_counter, if_else_counter;
    static void reset()
    {
      eq_counter = neq_counter = if_else_counter = 0;
    }
  };

  int grid2d::eq_counter      = 0;
  int grid2d::neq_counter     = 0;
  int grid2d::if_else_counter = 0;

  // Adapt as a bindable type for eve::product_type
  template<std::size_t I> constexpr int& get( grid2d& p) noexcept
  {
    if constexpr(I==0) return p.x; else if constexpr(I==1) return p.y;
  }

  template<std::size_t I> constexpr int get( grid2d const& p) noexcept
  {
    if constexpr(I==0) return p.x; else if constexpr(I==1) return p.y;
  }

  std::ostream& operator<<( std::ostream& os, grid2d const& p)
  {
    return os << "[x: " << p.x << " - y: " << p.y << "]";
  }

  //------------------------------------------------------------------------------------------------
  // Functions and operators are externally defined using tagged_dispatch
  //------------------------------------------------------------------------------------------------
  auto tagged_dispatch( eve::tag::is_equal_
                      , eve::same_value_type<grid2d> auto a
                      , eve::same_value_type<grid2d> auto b
                      )
  {
    grid2d::eq_counter++;
    return (get<0>(a) == get<0>(b)) &&(get<1>(a) == get<1>(b));
  }

  auto tagged_dispatch( eve::tag::is_not_equal_
                      , eve::same_value_type<grid2d> auto a
                      , eve::same_value_type<grid2d> auto b
                      )
  {
    grid2d::neq_counter++;
    return (get<0>(a) != get<0>(b)) || (get<1>(a) != get<1>(b));
  }

  template<typename Mask, eve::same_value_type<grid2d> T>
  auto tagged_dispatch( eve::tag::if_else_, Mask m, T const& a, T const& b )
  {
    grid2d::if_else_counter++;
    return T{ eve::if_else(m, get<0>(a), get<0>(b))
            , eve::if_else(m, get<1>(a), get<1>(b))
            };
  }

  template<typename Mask, eve::same_value_type<grid2d> T>
  auto tagged_dispatch( eve::tag::if_else_, Mask m, T const& a, eve::callable_zero_ )
  {
    grid2d::if_else_counter += 2;
    return T{ eve::if_else(m, get<0>(a), eve::zero), eve::if_else(m, get<1>(a), eve::zero) };
  }

  template<typename Mask, eve::same_value_type<grid2d> T>
  auto tagged_dispatch( eve::tag::if_else_, Mask m, eve::callable_zero_, T const& b )
  {
    grid2d::if_else_counter += 3;
    return T{ eve::if_else(m, eve::zero, get<0>(b)), eve::if_else(m, eve::zero, get<1>(b)) };
  }
}

// Opt-in for eve::product_type + adaptation
template<>              struct eve::is_product_type<udt::grid2d>  : std::true_type {};
template<>              struct std::tuple_size<udt::grid2d>       : std::integral_constant<std::size_t, 2> {};
template<std::size_t I> struct std::tuple_element<I,udt::grid2d> { using type = int; };
