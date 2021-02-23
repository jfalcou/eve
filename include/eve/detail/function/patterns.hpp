//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/swizzle.hpp>
#include <eve/detail/function/broadcast.hpp>
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
  };

  //================================================================================================
  // Look to see if a given pattern is optimizable and returns the optimized function object
  //================================================================================================
  template<int I0, int... I> consteval auto find_optimized_pattern()
  {
    [[maybe_unused]] constexpr auto sz = fixed<1+sizeof...(I)>{};
    [[maybe_unused]] constexpr auto p  = pattern_t<I0,I...>{};

          if constexpr( is_zero<I0,I...>        ) return bound{zero_swizzle{}       , sz};
    else  if constexpr( is_broadcast<I0,I...>   ) return bound{broadcast, index<I0> , sz};
    else  if constexpr( is_identity<I0,I...>    ) return bound{identity_swizzle{}   , sz};
    else                                          return bound{basic_swizzle        , p };
  }
}
