//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/product_type.hpp>
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

    // You're still responsible for your non-SIMD ordering
    friend constexpr auto operator<=>(grid2d,grid2d) = default;
  };

  // Adapt as a structured bindings compatible type for eve::product_type
  template<std::size_t I> constexpr int& get( grid2d& p) noexcept
  {
    if constexpr(I==0) return p.x; else if constexpr(I==1) return p.y;
  }

  template<std::size_t I> constexpr int get( grid2d const& p) noexcept
  {
    if constexpr(I==0) return p.x; else if constexpr(I==1) return p.y;
  }

  // Stream insertion is also on your behalf
  std::ostream& operator<<( std::ostream& os, grid2d const& p)
  {
    return os << "[x: " << p.x << " - y: " << p.y << "]";
  }
}

// Opt-in for eve::product_type + adaptation
template<>              struct eve::is_product_type<udt::grid2d>    : std::true_type {};
template<>              struct std::tuple_size<udt::grid2d>         : std::integral_constant<std::size_t, 2> {};
template<std::size_t I> struct std::tuple_element<I,udt::grid2d>    { using type = int; };

namespace udt
{
  //------------------------------------------------------------------------------------------------
  // This test UDT is made to be a placeholder for easier case where one just inherits from
  // kumi::tuple and adapt its interface
  //------------------------------------------------------------------------------------------------
  struct label_position : kumi::tuple<float, std::uint8_t>
  {
    friend auto&& position(eve::same_value_type<label_position> auto&& self) noexcept
    {
      return get<0>(std::forward<decltype(self)>(self));
    }

    friend auto&& label(eve::same_value_type<label_position> auto&& self) noexcept
    {
      return get<1>(std::forward<decltype(self)>(self));
    }
  };

  // Stream insertion is also on your behalf
  std::ostream& operator<<( std::ostream& os, label_position const& p)
  {
    return os << "'" << label(p) << "'@( " << position(p) << " )";
  }
}

// Opt-in for eve::product_type + adaptation
template<>  struct std::tuple_size<udt::label_position>       : std::integral_constant<std::size_t, 2> {};
template<>  struct std::tuple_element<0,udt::label_position>  { using type = float; };
template<>  struct std::tuple_element<1,udt::label_position>  { using type = std::uint8_t; };
