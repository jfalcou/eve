//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/expm1.hpp>

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
tanh_(EVE_SUPPORTS(cpu_), T a0) noexcept
{
  if constexpr( scalar_value<T> )
  {
    if( is_eqz(a0) ) return a0;
  }
  if constexpr( has_native_abi_v<T> )
  {
    auto x    = eve::abs(a0 + a0);
    auto test = x > T(0.5493) * 2;
    auto t    = expm1(x);
    auto rt2  = rec(t + T(2));
    if constexpr( scalar_value<T> )
    {
      auto r = test ? fnma(T(2), rt2, T(1)) : t * rt2;
      return is_negative(a0) ? -r : r;
    }
    else if constexpr( simd_value<T> )
    {
      auto z1 = fnma(T(2), rt2, T(1));
      auto z2 = t * rt2;
      auto r  = if_else(test, z1, z2);
      return copysign(r, a0);
    }
  }
  else { return apply_over(tanh, a0); }
}
}
