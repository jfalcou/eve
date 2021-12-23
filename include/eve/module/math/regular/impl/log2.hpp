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
#include <eve/constant/invlog_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/any.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sub.hpp>
#include <eve/module/real/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<floating_real_simd_value T, decorator D>
  EVE_FORCEINLINE constexpr T log2_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      using uiT   = as_integer_t<T, unsigned>;
      using iT    = as_integer_t<T, signed>;
      using elt_t = element_type_t<T>;
      if constexpr( std::is_same_v<elt_t, float> )
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
        ix     = (ix & 0x007fffff) + 0x3f3504f3;
        x      = bit_cast(ix, as<T>());
        T f    = dec(x);
        T s    = f / (2.0f + f);
        T z    = sqr(s);
        T w    = sqr(z);
        T t1   = w * horn<T, 0x3eccce13u, 0x3e789e26u>(w);
        T t2   = z * horn<T, 0x3f2aaaaau, 0x3e91e9eeu>(w);
        T R    = t2 + t1;
        T hfsq = half(eve::as<T>()) * sqr(f);

        T dk = float32(k);
        T r  = fma(fms(s, hfsq + R, hfsq) + f, invlog_2(eve::as<T>()), dk);
        // The original algorithm does some extra calculation in place of the return line
        // to get extra precision but this is uneeded for float as the exhaustive test shows
        // a 0.5 ulp maximal error on the full range.
        // Moreover all log2(exp2(i)) i =  1..31 are flint
        // I leave the code here in case an exotic proc will not play the game.
        //       T  hi = f - hfsq;
        //       hi =  (hi & uiT(0xfffff000ull));
        //       T  lo = fma(s, hfsq+R, f - hi - hfsq);
        //       T r = (lo+hi)*detail::Invlog_2lo<T>() + lo*detail::Invlog_2hi<T>() +
        //       hi*detail::Invlog_2hi<T>() + k;
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
        hx = ((hx & 0x000fffffull)) + 0x3fe6a09e;
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
        hi           = (hi & (allbits(eve::as<uiT>()) << 32));
        T lo         = fma(s, hfsq + R, f - hi - hfsq);

        T val_hi = hi * Invlog_2hi;
        T val_lo = fma(lo + hi, Invlog_2lo, lo * Invlog_2hi);

        T dk = float64(k);
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
      return apply_over(D()(log2), a0);
  }

  template<floating_real_scalar_value T, decorator D>
  EVE_FORCEINLINE constexpr auto log2_(EVE_SUPPORTS(cpu_), D const &, T x) noexcept
  {
    using uiT = as_integer_t<T, unsigned>;
    using iT  = as_integer_t<T, signed>;
    if constexpr( std::is_same_v<T, float> )
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
      return -(hfsq - (s * (hfsq + R)) - f) * invlog_2(eve::as<T>()) + k;
      // The original algorithm does some extra calculation in place of the return line
      // to get extra precision but this is uneeded for float as the exhaustive test shows
      // a 0.5 ulp maximal error on the full range.
      // Moreover all log2(exp2(i)) i =  1..31 are flint
      // I leave the code here in case an exotic proc will not play the game.
      //       T  hi = f - hfsq;
      //       hi =  bit_and(hi, uiT(0xfffff000ul));
      //       T  lo = fma(s, hfsq+R, f - hi - hfsq);
      //       return fma((lo+hi), Invlog_2lo<T>(), lo*Invlog_2hi<T>() + hi*Invlog_2hi<T>() + k);
    }
    else if constexpr( std::is_same_v<T, double> )
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_log2.c */
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
      {
        return x;
      }
      else if( x == one(eve::as<T>()) )
        return zero(eve::as<T>());
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      hx += 0x3ff00000 - 0x3fe6a09e;
      k += bit_cast(hx >> 20, as<iT>()) - 0x3ff;
      hx = (hx & 0x000fffff) + 0x3fe6a09e;
      x  = bit_cast((uint64_t)hx << 32 | ((bit_cast(x, as<uiT>()) & 0xffffffffull)), as<T>());
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
      T R = t2 + t1;
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
      T Invlog_2hi = Ieee_constant<T, 0x3fb8b000UL, 0x3ff7154765200000ULL>();
      T hi         = f - hfsq;
      hi           = bit_and(hi, (allbits(eve::as<uiT>()) << 32));
      T lo         = f - hi - hfsq + s * (hfsq + R);

      T val_hi = hi * Invlog_2hi;
      T val_lo = fma(lo + hi, Invlog_2lo, lo * Invlog_2hi);

      T dk = k;
      T w1 = dk + val_hi;
      val_lo += (dk - w1) + val_hi;
      val_hi = w1;
      return val_lo + val_hi;
    }
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T log2_(EVE_SUPPORTS(cpu_), T const &x) noexcept
  {
    return log2(regular_type(), x);
  }
}
