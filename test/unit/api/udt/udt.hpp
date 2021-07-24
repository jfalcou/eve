//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
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
    friend constexpr auto operator<=>(grid2d,grid2d) = default;
  };

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
}

// Opt-in for eve::product_type + adaptation
template<>              struct eve::is_product_type<udt::grid2d>  : std::true_type {};
template<>              struct std::tuple_size<udt::grid2d>       : std::integral_constant<std::size_t, 2> {};
template<std::size_t I> struct std::tuple_element<I,udt::grid2d> { using type = int; };
