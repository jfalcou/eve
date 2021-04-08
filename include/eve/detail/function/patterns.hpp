//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/swizzle.hpp>
#include <eve/detail/function/broadcast.hpp>
#include <eve/detail/function/swap_adjacent_groups.hpp>
#include <eve/detail/function/simd/common/patterns.hpp>

namespace eve::detail
{
  //================================================================================================
  // Wrap a callable with its additional constexpr info
  //================================================================================================
  template<typename Callable, typename... Args>
  struct bound
  {
    constexpr bound(Callable, Args...) {}
    template<typename W> auto operator()(W w) const noexcept { return Callable{}(w, Args{}...); }

    friend std::ostream& operator<<(std::ostream& os, bound)
    {
      os << Callable{} << "(";
      ((os << " " << Args{}),...);
      return os << " )";
      }
  };

  //================================================================================================
  // Look to see if a given pattern is optimizable and returns the optimized function object
  //================================================================================================
  template<int I0, int... I> consteval auto find_optimized_pattern()
  {
    [[maybe_unused]] constexpr auto sz = fixed<1+sizeof...(I)>{};
    [[maybe_unused]] constexpr auto p  = pattern_t<I0,I...>{};

          if constexpr( is_zero<I0,I...>        ) return bound{zero_swizzle{}      , sz};
    else  if constexpr( is_broadcast<I0,I...>   ) return bound{broadcast, index<I0>, sz};
    else  if constexpr( is_identity<I0,I...>    ) return bound{identity_swizzle{}  , p};
    else  if constexpr( is_swag<I0,I...> != sz  ) return bound{swap_adjacent_groups , is_swag<I0,I...>};
    else                                          return bound{basic_swizzle       , p};
  }
}
