//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/fms.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/is_less_equal.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_ngez.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/musl.hpp>
#include <eve/function/plain.hpp>
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

////////////////////////////////////////////////////////////////////////////////////
// Two implementations are given "musl_" and "plain_"
// They differ by the reduction step.
// The "plain" implementation of log is mainly for avx,  because avx does not have
// good support for integral vector types. "plain" uses frexp instead of ifrexp to run
// all the process with floating vector types
// The correct dispatch of log is done in each architecture related file or
// default to musl_
////////////////////////////////////////////////////////////////////////////////////

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto log_(EVE_SUPPORTS(cpu_)
                            , const T &xx) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    return musl_(log)(xx);
  }
  
  template<typename T>
  EVE_FORCEINLINE auto log_(EVE_SUPPORTS(cpu_)
                            , musl_type const &  
                            , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::log, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::log, a0);
    else
    {
      T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      using uiT = as_integer_t<T, unsigned>;
      using iT  = as_integer_t<T,   signed>;
      if constexpr(std::is_same_v<value_type_t<T>, float>)
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
        T x =  a0;
        iT k(0);
        auto isnez = is_nez(a0);
        logical<T> test; 
        if constexpr(eve::platform::supports_denormals)
        {
          test = is_less(a0, Smallestposval<T>())&&isnez;
          if (any(test))
          {
            k = sub[test](k, iT(23));
            x = if_else(test, x*T(8388608ul), x);
          }
        }
        uiT ix = bitwise_cast(x, as<uiT>());
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        ix += 0x3f800000 - 0x3f3504f3;
        k += bitwise_cast(ix>>23, as<iT>()) - 0x7f;
        ix = (ix&0x007fffff) + 0x3f3504f3;
        x =  bitwise_cast(ix, as<T>());
        T f = dec(x);
        T s = f/(2.0f + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3eccce13u, 0x3e789e26u>(w);
        T t2= z*horn<T, 0x3f2aaaaau, 0x3e91e9eeu>(w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
        
        T dk = tofloat(k);
        T r = fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo) - hfsq) + f));
        T zz; 
        if constexpr(eve::platform::supports_infinites)
        {
          zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
        }
        else
        {
          zz = if_else(isnez, r, Minf<T>());
        }
        return if_else(is_ngez(a0), eve::allbits_, zz);
      }
      else //if constexpr(std::is_same_v<value_type_t<T>, double>)
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
        using uiT = as_integer_t<T, unsigned>;
        using iT = as_integer_t<T,   signed>;
        T x =  a0;
        iT k(0);
        auto isnez = is_nez(a0);
        logical<T> test; 
        if constexpr(eve::platform::supports_denormals)
        {
          test = is_less(a0, Smallestposval<T>())&&isnez;
          if (any(test))
          {
            k = sub[test](k, iT(54));
            x = if_else(test, x*T(18014398509481984ull), x);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        uiT hx = bitwise_cast(x, as<uiT>()) >> 32;
        hx += 0x3ff00000 - 0x3fe6a09e;
        k += bitwise_cast(hx>>20, as<iT>()) - 0x3ff;
        hx = (bitwise_and(0x000fffffull, hx)) + 0x3fe6a09e;
        x = bitwise_cast(hx<<32 | (bitwise_and(0xffffffffull, bitwise_cast(x, as<uiT>()) )), as<T>());
        
        T f = dec(x);
        T s = f/(2.0f + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3fd999999997fa04ull, 0x3fcc71c51d8e78afull, 0x3fc39a09d078c69full > (w);
        T t2= z*horn<T, 0x3fe5555555555593ull, 0x3fd2492494229359ull
          , 0x3fc7466496cb03deull, 0x3fc2f112df3e5244ull> (w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
        
        T dk = tofloat(k);
        T r = fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo) - hfsq) + f));
        T zz; 
        if constexpr(eve::platform::supports_infinites)
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
  }
  
  template<typename T>
  EVE_FORCEINLINE auto log_(EVE_SUPPORTS(cpu_)
                            , plain_type const &  
                            , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::log, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::log, a0);
    else
    {
      T Log_2hi =  Ieee_constant<T, 0x3f318000U, 0x3fe62e42fee00000ULL>();
      T Log_2lo =  Ieee_constant<T, 0xb95e8083U, 0x3dea39ef35793c76ULL>();
      if constexpr(std::is_same_v<T, float>)
      {
        T xx =  a0;
        T dk = Zero<T>();
        auto isnez = is_nez(a0);
        logical<T> test;   
        if constexpr(eve::platform::supports_denormals)
        {
          auto test = is_less(a0, Smallestposval<T>())&&isnez;
          if (any(test))
          {
            dk =sub[test](dk, T(23));
            xx = if_else(test, xx*T(8388608ul), xx);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        
        auto [x, kk] = frexp(xx);
        auto x_lt_sqrthf = (Invsqrt_2<T>() > x);
        dk += dec[x_lt_sqrthf](kk);
        T f = dec(x+if_else(x_lt_sqrthf, x, eve::zero_));
        T s = f/(T(2) + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3eccce13, 0x3e789e26>(w);
        T t2= z*horn<T, 0x3f2aaaaa, 0x3e91e9ee>(w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
        T r = fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo) - hfsq) + f));
        T zz; 
        if constexpr(eve::platform::supports_infinites)
        {
          zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
        }
        else
        {
          zz = if_else(isnez, r, Minf<T>());
        }
        return if_else(eve::allbits_, is_ngez(a0), zz);
      }
      else //double
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
        T xx =  a0;
        T dk = Zero<T>();
        auto isnez = is_nez(a0);
        
        logical<T>  test = is_less(a0, Smallestposval<T>())&&isnez;
        if constexpr(eve::platform::supports_denormals)
        {
          if (any(test))
          {
            dk = sub[test](dk, T(54));
            xx = if_else(test, xx*T(18014398509481984ull), xx);
          }
        }
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        auto [x, kk] = frexp(xx);
        auto x_lt_sqrthf = (Invsqrt_2<T>() > x);
        dk += if_dec(x_lt_sqrthf, kk);
        T f = dec(x+if_else_zero(x_lt_sqrthf, x));
        T s = f/(T(2) + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
        T t2= z*horn<T, 0x3fe5555555555593ll, 0x3fd2492494229359ll
          , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
        T r = fma(dk, Log_2hi, ((fma(s, (hfsq+R), dk*Log_2lo) - hfsq) + f));
        T Invlog_2lo =  Ieee_constant<T, 0xb9389ad4U, 0x3de705fc2eefa200ULL>();
        T zz; 
        if constexpr(eve::platform::supports_infinites)
        {
          zz = if_else(isnez, if_else(a0 == Inf<T>(), Inf<T>(), r), Minf<T>());
        }
        
        else
        {
          zz = if_else(isnez, r, Minf<T>());
        }
        return if_else(eve::allbits_, is_ngez(a0), zz);
      }
    }
  }
}

#endif

