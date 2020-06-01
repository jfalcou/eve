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

#include <eve/concept/value.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/invsqrt_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/musl.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/plain.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/tofloat.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  // this implementation is better only if we are in avx_ without avx2_
  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto log_(EVE_SUPPORTS(cpu_), plain_type const &, const T &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      T Log_2hi   = Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      T Log_2lo   = Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T          xx    = a0;
        T          dk    = Zero<T>();
        auto       isnez = is_nez(a0);
        logical<T> test;
        if constexpr( eve::platform::supports_denormals )
        {
          auto test = is_less(a0, Smallestposval<T>()) && isnez;
          if( any(test) )
          {
            dk = sub[test](dk, T(23));
            xx = if_else(test, xx * T(8388608ul), xx);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */

        auto [x, kk]     = eve::frexp(xx);
        auto x_lt_sqrthf = (Invsqrt_2<T>() > x);
        dk += dec[x_lt_sqrthf](kk);
        T f    = dec(x + if_else(x_lt_sqrthf, x, eve::zero_));
        T s    = f / (T(2) + f);
        T z    = sqr(s);
        T w    = sqr(z);
        T t1   = w * horn<T, 0x3eccce13, 0x3e789e26>(w);
        T t2   = z * horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
        T R    = t2 + t1;
        T hfsq = Half<T>() * sqr(f);
        T r    = fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
        T zz;
        if constexpr( eve::platform::supports_infinites )
        {
          zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
        }
        else
        {
          zz = if_else(isnez, r, Minf<T>());
        }
        return if_else(is_ngez(a0), eve::allbits_, zz);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        /* origin: FreeBSD /usr/src/lib/msun/src/e_logf.c */
        /*
         * ====================================================
         * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
         *
         * Developed at SunPro, a Sun Microsystems, Inc. business.
         * Permission to use, copy, modify, and distribute this
         * software is freely granted, provided that this notice
         * is preserved.
         * ====================================================
         */
        //        using uiT = as_integer_t<T, unsigned>;
        T    xx    = a0;
        T    dk    = Zero<T>();
        auto isnez = is_nez(a0);

        logical<T> test = is_less(a0, Smallestposval<T>()) && isnez;
        if constexpr( eve::platform::supports_denormals )
        {
          if( any(test) )
          {
            dk = sub[test](dk, T(54));
            xx = if_else(test, xx * T(18014398509481984ull), xx);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        auto [x, kk]     = eve::frexp(xx);
        auto x_lt_sqrthf = (Invsqrt_2<T>() > x);
        dk += dec[x_lt_sqrthf](kk);
        T f  = dec(x + if_else(x_lt_sqrthf, x, eve::zero_));
        T s  = f / (T(2) + f);
        T z  = sqr(s);
        T w  = sqr(z);
        T t1 = w * horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll>(w);
        T t2 = z
               * horn<T,
                      0x3fe5555555555593ll,
                      0x3fd2492494229359ll,
                      0x3fc7466496cb03dell,
                      0x3fc2f112df3e5244ll>(w);
        T R    = t2 + t1;
        T hfsq = Half<T>() * sqr(f);
        T r    = fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
        T zz;
        if constexpr( eve::platform::supports_infinites )
        {
          zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
        }
        else
        {
          zz = if_else(isnez, r, Minf<T>());
        }
        return if_else(is_ngez(a0), eve::allbits_, zz);
      }
    }
    else
      return apply_over(plain_(log), a0);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation for avx
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto log_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v) noexcept
  {
    if constexpr( current_api < avx2 )
      return plain_(log)(v);
    else
      return musl_(log)(v);
  }
}

