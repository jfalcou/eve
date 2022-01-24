//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/constant/invsqrt_2.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto log2_(EVE_SUPPORTS(cpu_), plain_type const &, const T &a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T          xx    = a0;
        T          dk    = zero(eve::as<T>());
        auto       isnez = is_nez(a0);
        if constexpr( eve::platform::supports_denormals )
        {
          auto test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
          if( eve::any(test) )
          {
            dk = sub[test](dk, T(25));
            xx = if_else(test, xx * T(33554432ul), xx);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */

        auto [x, kk]     = eve::frexp(xx);
        auto x_lt_sqrthf = (invsqrt_2(eve::as<T>()) > x);
        dk += dec[x_lt_sqrthf](kk);
        T f    = dec(x + if_else(x_lt_sqrthf, x, eve::zero));
        T s    = f / (T(2) + f);
        T z    = sqr(s);
        T w    = sqr(z);
        T t1   = w * horn<T, 0x3eccce13, 0x3e789e26>(w);
        T t2   = z * horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
        T R    = t2 + t1;
        T hfsq = half(eve::as<T>()) * sqr(f);

        T r = fma(fms(s, hfsq + R, hfsq) + f, invlog_2(eve::as<T>()), dk);
        // The original algorithm does some extra calculation in place of the return line
        // to get extra precision but this is uneeded for float as the exhaustive test shows
        // a 0.5 ulp maximal error on the full range.
        // Moreover all log2(exp2(i)) i =  1..31 are flint
        // I leave the code here in case an exotic proc will not play the game.
        //       T  hi = f - hfsq;
        //       hi =  bit_and(hi, uiT(0xfffff000ull));
        //       T  lo = fma(s, hfsq+R, f - hi - hfsq);
        //       T r = (lo+hi)*Invlog_2lo<T>() + lo*Invlog_2hi<T>() + hi*Invlog_2hi<T>() + k;

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
        /* origin: FreeBSD /usr/src/lib/msun/src/e_log2f.c */
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
        using uiT  = as_integer_t<T, unsigned>;
        T    xx    = a0;
        T    dk    = zero(eve::as<T>());
        auto isnez = is_nez(a0);

        logical<T> test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
        if constexpr( eve::platform::supports_denormals )
        {
          if( eve::any(test) )
          {
            dk = sub[test](dk, T(54));
            xx = if_else(test, xx * T(18014398509481984ull), xx);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        auto [x, kk]     = eve::frexp(xx);
        auto x_lt_sqrthf = (invsqrt_2(eve::as<T>()) > x);
        dk += dec[x_lt_sqrthf](kk);
        T f  = dec(x + if_else(x_lt_sqrthf, x, eve::zero));
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
        T hfsq = half(eve::as<T>()) * sqr(f);
        //        return -(hfsq-(s*(hfsq+R))-f)*Invlog_2<T>()+dk;  // fast ?

        /*
         * f-hfsq must (for args near 1) be evaluated in extra precision
         * to avoid a large cancellation when x is near sqrt(2) or 1/sqrt(2).
         * This is fairly efficient since f-hfsq only depends on f, so can
         * be evaluated in parallel with R.  Not combining hfsq with R also
         * keeps R small (though not as small as a true `lo' term would be),
         * so that extra precision is not needed for terms involving R.
         *
         * Compiler bugs involving extra precision used to break Dekker's
         * theorem for spitting f-hfsq as hi+lo, unless double was used
         * or the multi-precision calculations were avoided when double
         * has extra precision.  These problems are now automatically
         * avoided as a side effect of the optimization of combining the
         * Dekker splitting step with the clear-low-bits step.
         *
         * y must (for args near sqrt(2) and 1/sqrt(2)) be added in extra
         * precision to avoid a very large cancellation when x is very near
         * these values.  Unlike the above cancellations, this problem is
         * specific to base 2.  It is strange that adding +-1 is so much
         * harder than adding +-ln2 or +-log10_2.
         *
         * This uses Dekker's theorem to normalize y+val_hi, so the
         * compiler bugs are back in some configurations, sigh.  And I
         * don't want to used double to avoid them, since that gives a
         * pessimization and the support for avoiding the pessimization
         * is not yet available.
         *
         * The multi-precision calculations for the multiplications are
         * routine.
         */

        /* hi+lo = f - hfsq + s*(hfsq+R) ~ log(1+f) */
        T Invlog_2lo = Ieee_constant<T, 0xb9389ad4U, 0x3de705fc2eefa200ULL>();
        T Invlog_2hi = Ieee_constant<T, 0x3fb8b000U, 0x3ff7154765200000ULL>();
        T hi         = f - hfsq;
        hi           = bit_and(hi, (allbits(eve::as<uiT>()) << 32));
        T lo         = fma(s, hfsq + R, f - hi - hfsq);

        T val_hi = hi * Invlog_2hi;
        T val_lo = fma(lo + hi, Invlog_2lo, lo * Invlog_2hi);

        T w1 = dk + val_hi;
        val_lo += (dk - w1) + val_hi;
        val_hi = w1;
        T r    = val_lo + val_hi;
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
      return apply_over(plain(log2), a0);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation for avx
  template<floating_real_scalar_value T, typename N>
  EVE_FORCEINLINE auto log2_(EVE_SUPPORTS(avx_), wide<T, N> const &v) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr( current_api < avx2 )
      return plain(log2)(v);
    else
      return musl_(log2)(v);
  }
}
