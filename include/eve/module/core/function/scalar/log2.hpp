//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LOG2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LOG2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/add.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/mul.hpp>
#include <eve/detail/function/musl.hpp>
#include <eve/detail/function/plain.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/invlog_2.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto log2_(EVE_SUPPORTS(cpu_)
                                      , T x) noexcept
  requires(T, floating_point<T>)
  {
    return musl_(log2)(x); 
  }
  
  
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto log2_(EVE_SUPPORTS(cpu_)
                                      , musl_type const &  
                                      , T x) noexcept
  requires(T, floating_point<T>)
  {
    using uiT = as_integer_t<T, unsigned>;
    using iT  = as_integer_t<T,   signed>;
    if constexpr(std::is_same_v<T, float>)
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
      uiT ix = bitwise_cast(x, as<uiT>());
      iT k = 0;
      if (ix < 0x00800000 || ix>>31)         /* x < 2**-126  */
      {
        if (ix<<1 == 0) return Minf<T>();  /* log(+-0)=-inf */
        if (ix>>31) return Nan<T>();       /* log(-#) = NaN */
        if constexpr(eve::platform::supports_denormals)
        {        /* subnormal number, scale up x */
          k -= 25;
          x *= 33554432.0f;
          ix = bitwise_cast(x, as<iT>());
        }
      }
      else if (ix >= 0x7f800000)
      {
        return x;
      }
      else if (ix == 0x3f800000)
        return 0;
      
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      ix += 0x3f800000 - 0x3f3504f3;
      k += bitwise_cast(ix>>23, as<iT>()) - 0x7f;
      ix = (ix&0x007fffff) + 0x3f3504f3;
      x =  bitwise_cast(ix, as<T>());
      T f = dec(x);
      T s = f/(2.0f + f);
      T z = sqr(s);
      T w = sqr(z);
      T t1 = w*horn<T, 0x3eccce13, 0x3e789e26>(w);
      T t2 = z*horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
      T R = t2 + t1;
      T hfsq = 0.5f*sqr(f);
      return -(hfsq-(s*(hfsq+R))-f)*Invlog_2<T>()+k;
      // The original algorithm does some extra calculation in place of the return line
      // to get extra precision but this is uneeded for float as the exhaustive test shows
      // a 0.5 ulp maximal error on the full range.
      // Moreover all log2(exp2(i)) i =  1..31 are flint
      // I leave the code here in case an exotic proc will not play the game.
      //       T  hi = f - hfsq;
      //       hi =  bitwise_and(hi, uiT(0xfffff000ul));
      //       T  lo = fma(s, hfsq+R, f - hi - hfsq);
      //       return fma((lo+hi), Invlog_2lo<T>(), lo*Invlog_2hi<T>() + hi*Invlog_2hi<T>() + k);
    }
    else //double
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
      uiT hx = bitwise_cast(x, as<uiT>()) >> 32;
      iT k = 0;
      if (hx < 0x00100000 || hx>>31)
      {
        if(is_eqz(x))
          return Minf<T>();  /* log(+-0)=-inf */
        if (hx>>31)
          return Nan<T>(); /* log(-#) = NaN */
        /* subnormal number, scale x up */
        if constexpr(eve::platform::supports_denormals)
        {
          k -= 54;
          x *=  18014398509481984.0;
          hx = bitwise_cast(x, as<uiT>()) >> 32;
        }
      }
      else if (hx >= 0x7ff00000)
      {
        return x;
      }
      else if (x == One<T>()) return Zero<T>();
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      hx += 0x3ff00000 - 0x3fe6a09e;
      k += bitwise_cast(hx>>20, as<iT>()) - 0x3ff;
      hx = (hx&0x000fffff) + 0x3fe6a09e;
      x = bitwise_cast( (uint64_t)hx<<32 | (bitwise_and(0xffffffffull, bitwise_cast(x, as<uiT>()))), as<T>());
      T f = dec(x);
      T hfsq = 0.5*sqr(f);
      T s = f/(2.0f + f);
      T z = sqr(s);
      T w = sqr(z);
      T t1= w*horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      T t2= z*horn<T, 0x3fe5555555555593ll, 0x3fd2492494229359ll
        , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
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
       * theorem for spitting f-hfsq as hi+lo, unless double_t was used
       * or the multi-precision calculations were avoided when double_t
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
       * don't want to used double_t to avoid them, since that gives a
       * pessimization and the support for avoiding the pessimization
       * is not yet available.
       *
       * The multi-precision calculations for the multiplications are
       * routine.
       */
      
      /* hi+lo = f - hfsq + s*(hfsq+R) ~ log(1+f) */
      
      T Invlog_2lo =  Ieee_constant<T, 0xb9389ad4U, 0x3de705fc2eefa200ULL>();
      T Invlog_2hi =  Ieee_constant<T, 0x3fb8b000UL, 0x3ff7154765200000ULL>();
      T  hi = f - hfsq;
      hi =  bitwise_and(hi, (Allbits<uiT>() << 32));
      T lo = f - hi - hfsq + s*(hfsq+R);
      
      T val_hi = hi*Invlog_2hi;
      T val_lo = fma(lo+hi, Invlog_2lo, lo*Invlog_2hi);
      
      T dk = k;
      T w1 = dk + val_hi;
      val_lo += (dk - w1) + val_hi;
      val_hi = w1;
      return val_lo + val_hi;
    }
  }
  
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto log2_(EVE_SUPPORTS(cpu_)
                                      , plain_type const &  
                                      , T x) noexcept
  requires(T, floating_point<T>)
  {
    return musl_(log2)(x); //the "plain" version of the algorithm is never speedier than the "musl" version.
    // the call is here to allow a scalar fallback to simd calls
  }
  
}

#endif
