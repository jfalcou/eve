//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LOG10_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LOG10_HPP_INCLUDED

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
  EVE_FORCEINLINE constexpr auto log10_(EVE_SUPPORTS(cpu_)
                                      , T x) noexcept
  requires(T, floating_point<T>)
  {
    return musl_(log10)(x); 
  }
  
  
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto log10_(EVE_SUPPORTS(cpu_)
                                      , musl_type const &  
                                      , T x) noexcept
  requires(T, floating_point<T>)
  {
    using uiT = as_integer_t<T, unsigned>;
    using iT  = as_integer_t<T,   signed>;
    T Invlog_10hi =  Ieee_constant<T, 0x3ede6000U, 0x3fdbcb7b15200000ULL>();
    T Invlog_10lo =  Ieee_constant<T, 0xb804ead9U, 0x3dbb9438ca9aadd5ULL>();
    T Log10_2hi   =  Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
    T Log10_2lo   =  Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>(); 
    if constexpr(std::is_same_v<T, float>)
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
      //      return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+k*Log_2olog_10<A0>(); // raw ?

      T hibits = f - hfsq;
      hibits =  bitwise_and(hibits, uiT(0xfffff000ul));
      T  lobits = fma(s, hfsq+R, f - hibits - hfsq);
      T dk = k;
      //      return ((((dk*Log10_2lo<T> + (lobits+hibits)*Invlog_10lo<T>()) + lobits*Invlog_10hi<T>()) + hibits*Invlog_10hi<T>()) + dk*Log10_2hi<T>());
      return fma(dk, Log10_2hi,
                 fma(hibits, Invlog_10hi,
                     fma(lobits, Invlog_10hi, fma(lobits+hibits, Invlog_10lo, dk*Log10_2lo))
                    )
                );
      
    }
    else //if constexpr(std::is_same_v<T, double>)
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
      else if (hx >= 0x7ff00000) return x;
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
      T dk = k;
      //          return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<T>()+dk*Log_2olog_10<T>(); //raw ?

      T  hi = f - hfsq;
      hi =  bitwise_and(hi, (Allbits<uiT>() << 32));
      T lo = f - hi - hfsq + s*(hfsq+R);
      T val_hi = hi*Invlog_10hi;
      T y = dk*Log10_2hi;
      T val_lo = fma(dk, Log10_2lo,  fma(lo+hi, Invlog_10lo,  lo*Invlog_10hi));
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
  
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto log10_(EVE_SUPPORTS(cpu_)
                                      , plain_type const &  
                                      , T x) noexcept
  requires(T, floating_point<T>)
  {
    return musl_(log10)(x); //the "plain" version of the algorithm is never speedier than the "musl" version.
    // the call is here to allow a scalar fallback to simd calls
  }
  
}

#endif
