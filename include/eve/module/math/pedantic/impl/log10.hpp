//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
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
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sub.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log10_(EVE_SUPPORTS(cpu_), pedantic_type const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using uiT     = as_integer_t<T, unsigned>;
      using iT      = as_integer_t<T, signed>;
      using elt_t   = element_type_t<T>;
      T Invlog_10hi = Ieee_constant<T, 0x3ede6000U, 0x3fdbcb7b15200000ULL>();
      T Invlog_10lo = Ieee_constant<T, 0xb804ead9U, 0x3dbb9438ca9aadd5ULL>();
      T Log10_2hi   = Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
      T Log10_2lo   = Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>();
      if constexpr( std::is_same_v<elt_t, float> )
      {
        /* origin: FreeBSD /usr/src/lib/msun/src/e_log10f.c */
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
        T          x = a0;
        iT         k(0);
        auto       isnez = is_nez(a0);
        logical<T> test;
        if constexpr( eve::platform::supports_denormals )
        {
          test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
          if( eve::any(test) )
          {
            k = sub[test](k, iT(25));
            x = if_else(test, x * T(33554432ul), x);
          }
        }
        uiT ix = bit_cast(x, as<uiT>());
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        ix += 0x3f800000 - 0x3f3504f3;
        k += bit_cast(ix >> 23, as<iT>()) - 0x7f;
        ix       = (ix & 0x007fffff) + 0x3f3504f3;
        x        = bit_cast(ix, as<T>());
        T f      = dec(x);
        T s      = f / (2.0f + f);
        T z      = sqr(s);
        T w      = sqr(z);
        T t1     = w * horn<T, 0x3eccce13u, 0x3e789e26u>(w);
        T t2     = z * horn<T, 0x3f2aaaaau, 0x3e91e9eeu>(w);
        T R      = t2 + t1;
        T hfsq   = half(eve::as<T>()) * sqr(f);
        T dk     = float32(k);
        T hibits = f - hfsq;
        hibits   = bit_and(hibits, uiT(0xfffff000ul));
        T lobits = fma(s, hfsq + R, f - hibits - hfsq);
        //      T r = ((((dk*log10_2lo + (lobits+hibits)*ivln10lo) + lobits*ivln10hi) +
        //      hibits*ivln10hi) + dk*log10_2hi);
        T r = fma(dk,
                  Log10_2hi,
                  fma(hibits,
                      Invlog_10hi,
                      fma(lobits, Invlog_10hi, fma(lobits + hibits, Invlog_10lo, dk * Log10_2lo))));
        T zz;
        if constexpr( eve::platform::supports_infinites )
        {
          zz = if_else(isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
        }
        else
        {
          zz = if_else(isnez, r, minf(eve::as<T>()));
        }
        return if_else(is_ngez(a0), eve::allbits, zz);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        /* origin: FreeBSD /usr/src/lib/msun/src/e_log10f.c */
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
        T          x = a0;
        iT         k(0);
        auto       isnez = is_nez(a0);
        logical<T> test;
        if constexpr( eve::platform::supports_denormals )
        {
          test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
          if( eve::any(test) )
          {
            k = sub[test](k, iT(54));
            x = if_else(test, x * T(18014398509481984ull), x);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        uiT hx = bit_cast(x, as<uiT>()) >> 32;
        hx += 0x3ff00000 - 0x3fe6a09e;
        k += bit_cast(hx >> 20, as<iT>()) - 0x3ff;
        hx = (bit_and(hx, 0x000fffffull)) + 0x3fe6a09e;
        x  = bit_cast(hx << 32 | (bit_and(bit_cast(x, as<uiT>()), 0xffffffffull)), as<T>());

        T f  = dec(x);
        T s  = f / (2.0f + f);
        T z  = sqr(s);
        T w  = sqr(z);
        T t1 = w * horn<T, 0x3fd999999997fa04ull, 0x3fcc71c51d8e78afull, 0x3fc39a09d078c69full>(w);
        T t2 = z
               * horn<T,
                      0x3fe5555555555593ull,
                      0x3fd2492494229359ull,
                      0x3fc7466496cb03deull,
                      0x3fc2f112df3e5244ull>(w);
        T R    = t2 + t1;
        T hfsq = half(eve::as<T>()) * sqr(f);
        T dk   = float64(k);
        //      T r = -(hfsq-(s*(hfsq+R))-f)*Invlog_10<T>()+dk*Log_2olog_10<T>(); // fast ?
        T hi     = f - hfsq;
        hi       = bit_and(hi, (allbits(eve::as<uiT>()) << 32));
        T lo     = f - hi - hfsq + s * (hfsq + R);
        T val_hi = hi * Invlog_10hi;
        T y      = dk * Log10_2hi;
        T val_lo = dk * Log10_2lo + (lo + hi) * Invlog_10lo + lo * Invlog_10hi;
        //
        //  Extra precision in for adding y is not strictly needed
        //  since there is no very large cancellation near x = sqrt(2) or
        //  x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
        //  with some parallelism and it reduces the error for many args.
        //
        T w1 = y + val_hi;
        val_lo += (y - w1) + val_hi;
        val_hi = w1;

        T r = val_lo + val_hi;
        T zz;
        if constexpr( eve::platform::supports_infinites )
        {
          zz = if_else(isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
        }
        else
        {
          zz = if_else(isnez, r, minf(eve::as<T>()));
        }
        return if_else(is_ngez(a0), eve::allbits, zz);
      }
    }
    else
      return apply_over(pedantic(log10), a0);
  }

  template<floating_real_scalar_value T, decorator D>
  EVE_FORCEINLINE constexpr auto log10_(EVE_SUPPORTS(cpu_), pedantic_type const &, T x) noexcept
  {
    using uiT     = as_integer_t<T, unsigned>;
    using iT      = as_integer_t<T, signed>;
    T Invlog_10hi = Ieee_constant<T, 0x3ede6000U, 0x3fdbcb7b15200000ULL>();
    T Invlog_10lo = Ieee_constant<T, 0xb804ead9U, 0x3dbb9438ca9aadd5ULL>();
    T Log10_2hi   = Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
    T Log10_2lo   = Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>();
    if constexpr( std::is_same_v<T, float> )
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_log10f.c */
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
      uiT ix = bit_cast(x, as<uiT>());
      iT  k  = 0;
      if( ix < 0x00800000 || ix >> 31 ) /* x < 2**-126  */
      {
        if( ix << 1 == 0 )
          return minf(eve::as<T>()); /* log(+-0)=-inf */
        if( ix >> 31 )
          return nan(eve::as<T>()); /* log(-#) = NaN */
        if constexpr( eve::platform::supports_denormals )
        { /* subnormal number, scale up x */
          k -= 25;
          x *= 33554432.0f;
          ix = bit_cast(x, as<iT>());
        }
      }
      else if( ix >= 0x7f800000 )
      {
        return x;
      }
      else if( ix == 0x3f800000 )
        return zero(eve::as(x));

      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      ix += 0x3f800000 - 0x3f3504f3;
      k += bit_cast(ix >> 23, as<iT>()) - 0x7f;
      ix     = (ix & 0x007fffff) + 0x3f3504f3;
      x      = bit_cast(ix, as<T>());
      T f    = dec(x);
      T s    = f / (2.0f + f);
      T z    = sqr(s);
      T w    = sqr(z);
      T t1   = w * horn<T, 0x3eccce13, 0x3e789e26>(w);
      T t2   = z * horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
      T R    = t2 + t1;
      T hfsq = 0.5f * sqr(f);
      //      return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+k*Log_2olog_10<A0>(); // raw ?

      T hibits = f - hfsq;
      hibits   = bit_and(hibits, uiT(0xfffff000ul));
      T lobits = fma(s, hfsq + R, f - hibits - hfsq);
      T dk     = k;
      //      return ((((dk*Log10_2lo<T> + (lobits+hibits)*Invlog_10lo<T>()) +
      //      lobits*Invlog_10hi<T>()) + hibits*Invlog_10hi<T>()) + dk*Log10_2hi<T>());
      return fma(dk,
                 Log10_2hi,
                 fma(hibits,
                     Invlog_10hi,
                     fma(lobits, Invlog_10hi, fma(lobits + hibits, Invlog_10lo, dk * Log10_2lo))));
    }
    else if constexpr( std::is_same_v<T, double> )
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_log10.c */
      /*
       * ====================================================
       * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
       *
       * Developed at SunSoft, a Sun Microsystems, Inc. business.
       * Permission to use, copy, modify, and distribute this
       * software is freely granted, provided that this notice
       * is preserved.
       * ====================================================
       */
      uiT hx = bit_cast(x, as<uiT>()) >> 32;
      iT  k  = 0;
      if( hx < 0x00100000 || hx >> 31 )
      {
        if( is_eqz(x) )
          return minf(eve::as<T>()); /* log(+-0)=-inf */
        if( hx >> 31 )
          return nan(eve::as<T>()); /* log(-#) = NaN */
        /* subnormal number, scale x up */
        if constexpr( eve::platform::supports_denormals )
        {
          k -= 54;
          x *= 18014398509481984.0;
          hx = bit_cast(x, as<uiT>()) >> 32;
        }
      }
      else if( hx >= 0x7ff00000 )
        return x;
      else if( x == one(eve::as<T>()) )
        return zero(eve::as<T>());
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      hx += 0x3ff00000 - 0x3fe6a09e;
      k += bit_cast(hx >> 20, as<iT>()) - 0x3ff;
      hx = (hx & 0x000fffff) + 0x3fe6a09e;
      x  = bit_cast((uint64_t)hx << 32 | (bit_and(0xffffffffull, bit_cast(x, as<uiT>()))), as<T>());
      T f    = dec(x);
      T hfsq = 0.5 * sqr(f);
      T s    = f / (2.0f + f);
      T z    = sqr(s);
      T w    = sqr(z);
      T t1   = w * horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll>(w);
      T t2   = z
             * horn<T,
                    0x3fe5555555555593ll,
                    0x3fd2492494229359ll,
                    0x3fc7466496cb03dell,
                    0x3fc2f112df3e5244ll>(w);
      T R  = t2 + t1;
      T dk = k;
      //          return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<T>()+dk*Log_2olog_10<T>(); //raw ?

      T hi     = f - hfsq;
      hi       = bit_and(hi, (allbits(eve::as<uiT>()) << 32));
      T lo     = f - hi - hfsq + s * (hfsq + R);
      T val_hi = hi * Invlog_10hi;
      T y      = dk * Log10_2hi;
      T val_lo = fma(dk, Log10_2lo, fma(lo + hi, Invlog_10lo, lo * Invlog_10hi));
      //
      //  Extra precision in for adding y is not strictly needed
      //  since there is no very large cancellation near x = sqrt(2) or
      //  x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
      //  with some parallelism and it reduces the error for many args.
      //
      T w1 = y + val_hi;
      val_lo += (y - w1) + val_hi;
      val_hi = w1;
      return val_lo + val_hi;
    }
  }
}
