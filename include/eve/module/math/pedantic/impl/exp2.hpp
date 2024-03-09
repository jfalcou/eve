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
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/constant/maxlog2.hpp>
#include <eve/module/math/constant/minlog2.hpp>
#include <eve/module/math/constant/minlog2denormal.hpp>

namespace eve::detail
{
  template<floating_ordered_value T, decorator D>
  EVE_FORCEINLINE constexpr T
  exp2_(EVE_SUPPORTS(cpu_), D const&, T x) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t    = element_type_t<T>;
      auto minlogval = []()
        {
          if constexpr( !eve::platform::supports_denormals ) return minlog2(eve::as<T>());
          else return minlog2denormal(eve::as<T>());
        };
      auto xltminlog2 = x <= minlogval();
      auto xgemaxlog2 = x >= maxlog2(eve::as(x));
      if constexpr( scalar_value<T> )
      {
        if( xgemaxlog2 ) return inf(eve::as(x));
        if( xltminlog2 ) return zero(eve::as(x));
      }
      auto k = nearest(x);
      x      = x - k;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T y =
          eve::reverse_horner(x, T(0x1.ebfbe2p-3f), T(0x1.c6add6p-5f), T(0x1.3b2844p-7f)
                             , T(0x1.602430p-10f), T(0x1.459188p-13f));
        x   = inc(fma(y, sqr(x), x * log_2(eve::as<T>())));
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        x *= log_2(eve::as<T>());
        T    t = sqr(x);
        auto h =
          eve::reverse_horner(t, T(0x1.555555555553ep-3), T(-0x1.6c16c16bebd93p-9), T(0x1.1566aaf25de2cp-14)
                             , T(-0x1.bbd41c5d26bf1p-20), T(0x1.6376972bea4d0p-25));
        T    c = fnma(t, h, x); // x-h*t
        x      = oneminus(((-(x * c) / (T(2) - c)) - x));
      }
      auto z = ldexp[pedantic](x, k);
      if constexpr( simd_value<T> )
      {
        z = if_else(xltminlog2, eve::zero, z);
        z = if_else(xgemaxlog2, inf(eve::as(x)), z);
      }
      return z;
    }
    else { return apply_over(D()(exp2), x); }
  }
}
