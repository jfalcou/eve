//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<value T, auto I0, auto I1>
  EVE_FORCEINLINE T
  swap_pairs_(EVE_SUPPORTS(cpu_), T x
                  , std::integral_constant<size_t, I0> const &
                  , std::integral_constant<size_t, I1> const &  ) noexcept
  {
    constexpr size_t C = cardinal_v<T>;
    EVE_ASSERT((I0 < C) && (I1 < C), "some index(es) are out or range");
    if constexpr(simd_value<T>)
    {
      constexpr size_t C = cardinal_v<T>;
      EVE_ASSERT(I0 < C && I1 < C, "some index(es) are out or range");
      auto p = [](auto i,  auto){
       return (i == I0) ? I1 :(i == I1 ? I0 : i) ;
      };
      return eve::shuffle(x, eve::as_pattern(p));
    }
    else if constexpr(scalar_value<T>)
    {
      EVE_ASSERT(I0 < 1 && I1 < 1, "some index(es) are out or range");
      return x;
    }
  }
}
