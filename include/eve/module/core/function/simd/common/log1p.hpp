//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG1P_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG1P_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/detail/function/musl.hpp>
#include <eve/detail/function/plain.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/tofloat.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/ieee_constant.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/invsqrt_2.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/zero.hpp>
#include <eve/module/core/detail/generic/horn.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <tuple>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>


namespace eve::detail
{ 
  template<floating_real_value T>
  EVE_FORCEINLINE auto log1p_(EVE_SUPPORTS(cpu_)
                             , plain_type const &  
                             , const T &a0) noexcept
  {
    if constexpr(native<T>) 
    {
      /* origin: FreeBSD /usr/src/lib/msun/src/e_log1p(f).c */
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
      T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      T uf =  inc(a0);
      auto isnez = is_nez(uf);
      auto [x, k] = frexp(uf);
      auto  x_lt_sqrthf = (Invsqrt_2<T>() >  x);
      /* reduce x into [sqrt(2)/2, sqrt(2)] */
      k = dec[x_lt_sqrthf](k);
      T f = dec(x+if_else(x_lt_sqrthf, x, eve::zero_));
      /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
      T  c = if_else( k >= 2, oneminus(uf-a0), a0-dec(uf))/uf;
      T hfsq = Half<T>()*sqr(f);
      T s = f/(2.0f + f);
      T z = sqr(s);
      T w = sqr(z);
      T t1, t2; 
      if constexpr(std::is_same_v<value_type_t<T>, float>)
      {
        t1= w*horn<T, 0x3eccce13, 0x3e789e26>(w);
        t2= z*horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
      }
      else //if constexpr(std::is_same_v<value_type_t<T>, double>)
      {
        t1= w*horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
        t2= z*horn<T, 0x3fe5555555555593ll, 0x3fd2492494229359ll, 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
      }
      T R = t2 + t1;
      T r = fma(k, Log_2hi, ((fma(s, (hfsq+R), k*Log_2lo+c) - hfsq) + f));
      T zz; 
      if constexpr(eve::platform::supports_infinites)
      {
        zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
      }
      else
      {
        zz = if_else(isnez, r, Minf<T>());
      }
      return if_else(is_ngez(uf), eve::allbits_, zz);
    }
    else return apply_over(musl_(log), a0); 
  }
  
  template<floating_real_simd_value T>
  EVE_FORCEINLINE auto log1p_(EVE_SUPPORTS(cpu_)
                            , musl_type const &  
                            , const T &a0) noexcept
  {
    if constexpr(native<T>) 
    {
      using elt_t =  value_type_t<T>; 
      using uiT = as_integer_t<T, unsigned>;
      using iT  = as_integer_t<T,   signed>;
      T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      const T uf =  inc(a0);
      auto isnez = is_nez(uf);
      if constexpr(std::is_same_v<elt_t, float>)
      {
        uiT iu = bit_cast(uf, as<uiT>());
        iu += 0x3f800000 - 0x3f3504f3;
        iT k = bit_cast(iu>>23, as<iT>()) - 0x7f;
        /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        iu = (iu&0x007fffff) + 0x3f3504f3;
        T f =  dec(bit_cast(iu, as<T>()));
        T s = f/(2.0f + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3eccce13, 0x3e789e26>(w);
        T t2= z*horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
        T dk = tofloat(k);
        T  c = if_else( k >= 2, oneminus(uf-a0), a0-dec(uf))/uf;
        T r = fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo+c) - hfsq) + f));
        T zz; 
        if constexpr(eve::platform::supports_infinites)
        {
          zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
        }
        else
        {
          zz = if_else(isnez, r, Minf<T>());
        } 
        return if_else(is_ngez(uf), eve::allbits_, zz);
      }
      else if constexpr(std::is_same_v<elt_t, double>)
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
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        uiT hu = bit_cast(uf, as<uiT>())>>32;
        hu += 0x3ff00000 - 0x3fe6a09e;
        iT k = bit_cast(hu>>20, as<iT>() ) - 0x3ff;
        /* correction term ~ log(1+x)-log(u), avoid underflow in c/u */
        T  c =  if_else( k >= 2, oneminus(uf-a0), a0-dec(uf))/uf;
        hu =  (hu&0x000fffffull) + 0x3fe6a09e;
        T f = bit_cast( bit_cast(hu<<32, as<uiT>()) | (bit_and( bit_cast(uf, as<uiT>()),0xffffffffull)), as<T>());
        f = dec(f);
        
        T hfsq = Half<T>()*sqr(f);
        T s = f/(2.0 + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
        T t2= z*horn<T, 0x3fe5555555555593ll, 0x3fd2492494229359ll
          , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
        T R = t2 + t1;
        T dk = tofloat(k);
        T r = fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo+c) - hfsq) + f)); 
        T zz; 
        if constexpr(eve::platform::supports_infinites)
        {
          zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
        }
        else
        {
          zz = if_else(isnez, r, Minf<T>());
        } 
        return if_else(is_ngez(uf), eve::allbits_, zz);
      }
    }
    else return apply_over(musl_(log), a0); 
  }
}

#endif

