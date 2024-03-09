//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/constant/minlog.hpp>
#include <eve/module/math/constant/minlogdenormal.hpp>
#include <eve/module/math/regular/reverse_horner.hpp>

namespace eve::detail
{
  template<floating_ordered_value T>
  EVE_FORCEINLINE constexpr T
  exp_(EVE_SUPPORTS(cpu_), T x) noexcept
  {
    auto isnan = is_nan(x);
    if constexpr( scalar_value<T> )
    {
      if constexpr( has_emulated_abi_v<wide<T>> )
      {
        return (x <= eve::minlog(as(x))) ? T(0)
          : ((x >= eve::maxlog(as(x))) ? inf(as(x)) : std::exp(x));
      }
      else
      {
        wide<T> xx(x);
        return exp(xx).get(0);
      }
    }
    else if constexpr( has_native_abi_v<T> )
    {
      using elt_t       = element_type_t<T>;
      auto    minlogval = []() { return minlog(eve::as<T>()); };
      const T Log_2hi   = ieee_constant<0x1.6300000p-1f, 0x1.62e42fee00000p-1>(eve::as<T>{});
      const T Log_2lo   = ieee_constant<-0x1.bd01060p-13f, 0x1.a39ef35793c76p-33>(eve::as<T>{});
      const T Invlog_2  = ieee_constant<0x1.7154760p+0f, 0x1.71547652b82fep+0>(eve::as<T>{});
      auto    xltminlog = x <= minlogval();
      auto    xgemaxlog = x >= maxlog(eve::as(x));
      if constexpr( scalar_value<T> )
      {
        if( isnan ) return nan(as(x));
        if( xgemaxlog ) return inf(eve::as(x));
        if( xltminlog ) return zero(eve::as(x));
      }
      auto c = nearest(Invlog_2 * x);
      auto k = c;
      x      = fnma(c, Log_2hi, x); // x-c*L
      if constexpr( std::is_same_v<elt_t, float> )
      {
        x      = fnma(c, Log_2lo, x);
        auto y =
          eve::reverse_horner(x, T(0x1.000000p-1f), T(0x1.55534ap-3f), T(0x1.5552aep-5f)
                             , T(0x1.131b16p-7f), T(0x1.6ef19ep-10f));
        ;
        c      = inc(fma(y, sqr(x), x));
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        auto hi = x;
        auto lo = c * Log_2lo;
        x       = hi - lo;
        auto t  = sqr(x);
        c       = fnma(t,

                       eve::reverse_horner(t, T(0x1.555555555553ep-3), T(-0x1.6c16c16bebd93p-9), T(0x1.1566aaf25de2cp-14)
                                          , T(-0x1.bbd41c5d26bf1p-20), T(0x1.6376972bea4d0p-25)), x); // x-h*t
        c       = oneminus((((lo - (x * c) / (T(2) - c)) - hi)));
      }
      auto z = ldexp[pedantic](c, k);
      if constexpr( simd_value<T> )
      {
        z = if_else(xltminlog, eve::zero, z);
        z = if_else(xgemaxlog, inf(eve::as(x)), z);
        z = if_else(isnan, allbits, z);
      }
      return z;
    }
    else return apply_over(exp, x);
  }

// -----------------------------------------------------------------------------------------------
// Masked case
  template<conditional_expr C, value U>
  EVE_FORCEINLINE auto
  exp_(EVE_SUPPORTS(cpu_), C const& cond, U const& t) noexcept
  {
    return mask_op(cond, eve::exp, t);
  }
}
