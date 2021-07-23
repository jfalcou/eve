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
  struct grid2d
  {
    // Opt-in for eve::product_type
    using is_product_type = void;

    // Retrieve the actual sub-part of the UDT even when vectorized
    template<eve::same_value_type<grid2d> P> friend constexpr decltype(auto) x(P&& p) noexcept
    {
      return eve::content<0>(std::forward<P>(p));
    }

    template<eve::same_value_type<grid2d> P> friend constexpr decltype(auto) y(P&& p) noexcept
    {
      return eve::content<1>(std::forward<P>(p));
    }

    // Actual data
    int x = +1, y = -1;
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
}

// Adapt as a bindable type for eve::product_type
namespace std
{
  template<> struct tuple_size<udt::grid2d> : std::integral_constant<std::size_t, 2> {};

  template<std::size_t I> struct tuple_element<I,udt::grid2d>
  {
    using type = int;
  };
}

namespace udt
{
  //------------------------------------------------------------------------------------------------
  // Actual interface - Note that we mix function and friend function to check both works
  //------------------------------------------------------------------------------------------------
  template<eve::same_value_type<grid2d> P>
  std::ostream& operator<<( std::ostream& os, P const& p)
  {
    return os << "[x: " << x(p) << " - y: " << y(p) << "]\n";
  }
}
