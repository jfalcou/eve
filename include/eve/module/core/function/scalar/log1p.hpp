//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LOG1P_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LOG1P_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/add.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/mul.hpp>
#include <eve/detail/function/musl.hpp>
#include <eve/function/oneminus.hpp>
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
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto log1p_(EVE_SUPPORTS(cpu_)
                                      , T x) noexcept
  {
    return musl_(log1p)(x); 
  }
  
  template<floating_real_scalar_value T>
  EVE_FORCEINLINE constexpr auto log1p_(EVE_SUPPORTS(cpu_)
                                       , musl_type const &  
                                       , T x) noexcept
  {
    using uiT = as_integer_t<T, unsigned>;
    using iT  = as_integer_t<T,   signed>;
    T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
    T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
    if constexpr(std::is_same_v<T, float>)
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_log1pf.c */
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
      iT k = 1;
      T c = Zero<T>(), f = x;
      if (ix < 0x3ed413d0 || ix>>31)               /* 1+x < sqrt(2)+  */
      {
        if (ix >= 0xbf800000)                       /* x <= -1.0 */
        {
          if (x == Mone<T>())  return Minf<T>();  /* log1p(-1)=-inf */
          return Nan<T>();                         /* log1p(x<-1)=NaN */
        }
        if (ix<<1 < 0x33800000<<1)                  /* |x| < 2**-24 */
        {
          if ((ix&0x7f800000) == 0) return x;
        }
        if (ix <= 0xbe95f619)                       /* sqrt(2)/2- <= 1+x < sqrt(2)+ */
        {
          k = 0;
        }
      }
      else if (ix >= 0x7f800000)  return x;
      if (k)
      {
        /* reduce u into [sqrt(2)/2, sqrt(2)] */
        T uf =  inc(x);
        uiT iu = bit_cast(uf, as<uiT>());
        iu += 0x3f800000 - 0x3f3504f3;
        k = bit_cast(iu>>23, as<iT>()) - 0x7f;
        /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
        if (k < 25)
        {
          c = k >= 2 ? oneminus(uf-x) : x-dec(uf);
          c /= uf;
        }

        /* reduce u into [sqrt(2)/2, sqrt(2)] */
        iu = (iu&0x007fffff) + 0x3f3504f3;
        f =  dec(bit_cast(iu, as<T>()));
      }
      T s = f/(2.0f + f);
      T z = sqr(s);
      T w = sqr(z);
      T t1= w*horn<T, 0x3eccce13, 0x3e789e26>(w);
      T t2= z*horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
      T R = t2 + t1;
      T hfsq = 0.5f*sqr(f);
      T dk = k;
      return  fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo+c) - hfsq) + f));
    }
    else if constexpr(std::is_same_v<T, double>)
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_log1p.c */
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
      iT k = 1;
      
      T c = Zero<T>();
      T f = x;
      if (hx < 0x3fda827a || hx>>31)               /* 1+x < sqrt(2)+ */
      {
        if (hx >= 0xbff00000)                      /* x <= -1.0 */
        {
          if (x == Mone<T>()) return Minf<T>();  /* log1p(-1)=-inf */
          return Nan<T>();                        /* log1p(x<-1)=NaN */
        }
        if (hx<<1 < 0x3ca00000<<1)                 /* |x| < 2**-53 */
        {
          if ((hx&0x7ff00000) == 0) return x;
        }
        if (hx <= 0xbfd2bec4)                      /* sqrt(2)/2- <= 1+x < sqrt(2)+ */
        {
          k = 0;
        }
      } else if (hx >= 0x7ff00000) return x;
      if (k)
      {
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        T uf =  inc(x);
        uiT hu = bit_cast(uf, as<uiT>())>>32;
        hu += 0x3ff00000 - 0x3fe6a09e;
        k = (int)(hu>>20) - 0x3ff;
        /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
        if (k < 54)
        {
          c = k >= 2 ? oneminus(uf-x) : x-dec(uf);
          c /= uf;
        }
        hu =  (hu&0x000fffff) + 0x3fe6a09e;
        f = bit_cast( bit_cast(hu<<32, as<uiT>()) | (bit_and( bit_cast(uf, as<uiT>()), 0xffffffffull)), as<T>());
        f = dec(f);
      }

      T hfsq = 0.5*sqr(f);
      T s = f/(2.0f + f);
      T z = sqr(s);
      T w = sqr(z);
      T t1= w*horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
      T t2= z*horn<T, 0x3fe5555555555593ll, 0x3fd2492494229359ll, 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      T R = t2 + t1;
      T dk = k;
      return  fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo+c) - hfsq) + f));
    } 
  }
  
  template<floating_real_scalar_value T>
  EVE_FORCEINLINE constexpr auto log1p_(EVE_SUPPORTS(cpu_)
                                      , plain_type const &  
                                      , T x) noexcept
  {
    return musl_(log1p)(x); //the "plain" scalar version of the algorithm is never speedier than the "musl" version.
    // the call is here to allow a scalar fallback to simd calls
  }
  
}

#endif
