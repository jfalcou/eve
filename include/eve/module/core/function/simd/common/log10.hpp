//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG10_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG10_HPP_INCLUDED
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/any.hpp>
#include <eve/function/bitwise_and.hpp>
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


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto log10_(EVE_SUPPORTS(cpu_)
                            , const T &xx) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    return musl_(log10)(xx);
  }
  
  template<typename T>
  EVE_FORCEINLINE auto log10_(EVE_SUPPORTS(cpu_)
                            , musl_type const &  
                            , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::log10, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::log10, a0);
    else
    {
      using uiT = as_integer_t<T, unsigned>;
      using iT  = as_integer_t<T,   signed>;
      T Invlog_10hi =  Ieee_constant<T, 0x3ede6000U, 0x3fdbcb7b15200000ULL>();
      T Invlog_10lo =  Ieee_constant<T, 0xb804ead9U, 0x3dbb9438ca9aadd5ULL>();
      T Log10_2hi   =  Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
      T Log10_2lo   =  Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>(); 
      if constexpr(std::is_same_v<value_type_t<T>, float>)
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
        T x =  a0;
        iT k(0);
        auto isnez = is_nez(a0);
        logical<T> test; 
        if constexpr(eve::platform::supports_denormals)
        {
          test = is_less(a0, Smallestposval<T>())&&isnez;
          if (any(test))
          {
            k = sub[test](k, iT(25));
            x = if_else(test, x*T(33554432ul), x);
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
        T  hibits = f - hfsq;
        hibits =  bitwise_and(hibits, uiT(0xfffff000ul));
        T  lobits = fma(s, hfsq+R, f - hibits - hfsq);
        //      T r = ((((dk*log10_2lo + (lobits+hibits)*ivln10lo) + lobits*ivln10hi) + hibits*ivln10hi) + dk*log10_2hi);
        T r = fma(dk, Log10_2hi,
                  fma(hibits, Invlog_10hi,
                      fma(lobits, Invlog_10hi, fma(lobits+hibits, Invlog_10lo, dk*Log10_2lo))
                     )
                 );
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
        T dk =  tofloat(k); 
        //      T r = -(hfsq-(s*(hfsq+R))-f)*Invlog_10<T>()+dk*Log_2olog_10<T>(); // fast ?
        T  hi = f - hfsq;
        hi =  bitwise_and(hi, (Allbits<uiT>() << 32));
        T lo = f - hi - hfsq + s*(hfsq+R);
        T val_hi = hi*Invlog_10hi;
        T  y = dk*Log10_2hi;
        T  val_lo = dk*Log10_2lo + (lo+hi)*Invlog_10lo + lo*Invlog_10hi;
        //  
        //  Extra precision in for adding y is not strictly needed
        //  since there is no very large cancellation near x = sqrt(2) or
        //  x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
        //  with some parallelism and it reduces the error for many args.
        //  
        T w1 = y + val_hi;
        val_lo += (y - w1) + val_hi;
        val_hi = w1;
        
        T r =  val_lo + val_hi;
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
  EVE_FORCEINLINE auto log10_(EVE_SUPPORTS(cpu_)
                            , plain_type const &  
                            , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::log10, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::log10, a0);
    else
    {
      T Invlog_10hi =  Ieee_constant<T, 0x3ede6000U, 0x3fdbcb7b15200000ULL>();
      T Invlog_10lo =  Ieee_constant<T, 0xb804ead9U, 0x3dbb9438ca9aadd5ULL>();
      T Log10_2hi   =  Ieee_constant<T, 0x3e9a0000U, 0x3fd3440000000000ULL>();
      T Log10_2lo   =  Ieee_constant<T, 0x39826a14U, 0x3ed3509f79fef312ULL>(); 
      if constexpr(std::is_same_v<value_type_t<T>, float>)
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
        T xx =  a0;
        T dk = Zero<T>();
        auto isnez = is_nez(a0);
        logical<T> test;   
        if constexpr(eve::platform::supports_denormals)
        {
          auto test = is_less(a0, Smallestposval<T>())&&isnez;
          if (any(test))
          {
            dk =sub[test](dk, T(25));
            xx = if_else(test, xx*T(33554432ul), xx);
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
        T  hi = f - hfsq;
        hi =  bitwise_and(hi, 0xfffff000u);
        T  lo = fma(s, hfsq+R, f - hi - hfsq);
        T r = fma(dk, Log10_2hi,
                  fma(hi, Invlog_10hi,
                      fma(lo, Invlog_10hi,
                          fma(lo+hi, Invlog_10lo, dk*Log10_2lo))
                     )
                 );       
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
      else // if constexpr(std::is_same_v<value_type_t<T>, double)
      {
        /* origin: FreeBSD /usr/src/lib/msun/src/e_log10.c */
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
        dk += dec[x_lt_sqrthf](kk);
        T f = dec(x+if_else(x_lt_sqrthf, x, eve::zero_));
        T s = f/(T(2) + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3fd999999997fa04ll, 0x3fcc71c51d8e78afll, 0x3fc39a09d078c69fll > (w);
        T t2= z*horn<T, 0x3fe5555555555593ll, 0x3fd2492494229359ll
          , 0x3fc7466496cb03dell, 0x3fc2f112df3e5244ll> (w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
        //      T r = -(hfsq-(s*(hfsq+R))-f)*Invlog_10<T>()+dk*Log_2olog_10<T>(); // fast ?
        T  hi = f - hfsq;
        hi =  bitwise_and(hi, (Allbits<uiT>() << 32));
        T lo = f - hi - hfsq + s*(hfsq+R);
        T val_hi = hi*Invlog_10hi;
        T  y = dk*Log10_2hi;
        T  val_lo = dk*Log10_2lo + (lo+hi)*Invlog_10lo + lo*Invlog_10hi;
        //  
        //  Extra precision in for adding y is not strictly needed
        //  since there is no very large cancellation near x = sqrt(2) or
        //  x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
        //  with some parallelism and it reduces the error for many args.
        //  
        T w1 = y + val_hi;
        val_lo += (y - w1) + val_hi;
        val_hi = w1;
        T r =  val_lo + val_hi;
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
}

#endif

