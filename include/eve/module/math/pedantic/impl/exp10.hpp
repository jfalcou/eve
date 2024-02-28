//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/core/detail/generic/horn1.hpp>
#include <eve/module/math/constant/invlog10_2.hpp>
#include <eve/module/math/constant/maxlog10.hpp>
#include <eve/module/math/constant/minlog10denormal.hpp>
#include <eve/module/math/constant/minlogdenormal.hpp>

namespace eve::detail
{
template<floating_ordered_value T, decorator D>
EVE_FORCEINLINE constexpr T
exp10_(EVE_SUPPORTS(cpu_), pedantic_type const&, T x) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    using elt_t    = element_type_t<T>;
    auto minlogval = []()
    {
      if constexpr( (!eve::platform::supports_denormals) ) { return minlog10(eve::as<T>()); }
      else { return minlog10denormal(eve::as<T>()); }
    };
    const T Log10_2hi   = ieee_constant<0x1.3400000p-2f, 0x1.3440000000000p-2>(eve::as<T>{});
    const T Log10_2lo   = ieee_constant<0x1.04d4280p-12f, 0x1.3509f79fef312p-18>(eve::as<T>{});
    auto    xltminlog10 = x <= minlogval();
    auto    xgemaxlog10 = x >= maxlog10(eve::as(x));
    if constexpr( scalar_value<T> )
    {
      if( xgemaxlog10 ) return inf(eve::as(x));
      if( xltminlog10 ) return zero(eve::as(x));
    }
    auto c = nearest(invlog10_2(eve::as<T>()) * x);
    auto k = c;
    x      = fnma(c, Log10_2hi, x); // x-c*L
    x      = fnma(c, Log10_2lo, x);
    if constexpr( std::is_same_v<elt_t, float> )
    {
      c = inc(
      eve::reverse_horner(x, T(0x1.26bb1cp+1f), T(0x1.53524cp+1f), T(0x1.046fb4p+1f)
                         , T(0x1.2bd698p+0f), T(0x1.1559dep-1f), T(0x1.a9bfe2p-3f)) * x);
    }
    else if constexpr( std::is_same_v<elt_t, double> )
    {
      T xx = sqr(x);
      T px = x
             *
             eve::reverse_horner(xx, T(0x1.2b4798e134a01p+11), T(0x1.96b7a050349e4p+8)
                                , T(0x1.77d9474c55934p+3), T(0x1.4fd75f3062dd4p-5));
      T x2 = px / ( eve::reverse_horner(xx, T(0x1.03f37650df6e2p+11), T(0x1.3e05eefd67782p+10)
                                       , T(0x1.545fdce51ca08p+6), T(0x1.0p0)) - px);
      c = inc(x2 + x2);
    }
    auto z = ldexp[pedantic](c, k);
    if constexpr( simd_value<T> )
    {
      z = if_else(xltminlog10, eve::zero, z);
      z = if_else(xgemaxlog10, inf(eve::as(x)), z);
    }
    return z;
  }
  else return apply_over(pedantic(exp10), x);
}
}
