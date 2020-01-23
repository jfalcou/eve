//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_COMMON_SIMD_LOG2_HPP_INCLUDED
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


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE auto log2_(EVE_SUPPORTS(cpu_)
                            , const T &xx) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    return musl_(log2)(xx);
  }
  
  template<typename T>
  EVE_FORCEINLINE auto log2_(EVE_SUPPORTS(cpu_)
                            , musl_type const &  
                            , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::log2, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::log2, a0);
    else
    {
      using uiT = as_integer_t<T, unsigned>;
      using iT  = as_integer_t<T,   signed>;
      if constexpr(std::is_same_v<value_type_t<T>, float>)
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
        uiT ix = bit_cast(x, as<uiT>());
        /* reduce x into [sqrt(2)/2, sqrt(2)] */
        ix += 0x3f800000 - 0x3f3504f3;
        k += bit_cast(ix>>23, as<iT>()) - 0x7f;
        ix = (ix&0x007fffff) + 0x3f3504f3;
        x =  bit_cast(ix, as<T>());
        T f = dec(x);
        T s = f/(2.0f + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3eccce13u, 0x3e789e26u>(w);
        T t2= z*horn<T, 0x3f2aaaaau, 0x3e91e9eeu>(w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
        
        T dk = tofloat(k);
        T r =   fma(fms(s, hfsq+R, hfsq)+f, Invlog_2<T>(), dk);
        // The original algorithm does some extra calculation in place of the return line
        // to get extra precision but this is uneeded for float as the exhaustive test shows
        // a 0.5 ulp maximal error on the full range.
        // Moreover all log2(exp2(i)) i =  1..31 are flint
        // I leave the code here in case an exotic proc will not play the game.
        //       T  hi = f - hfsq;
        //       hi =  bit_and(hi, uiT(0xfffff000ull));
        //       T  lo = fma(s, hfsq+R, f - hi - hfsq);
        //       T r = (lo+hi)*detail::Invlog_2lo<T>() + lo*detail::Invlog_2hi<T>() + hi*detail::Invlog_2hi<T>() + k;
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
        uiT hx = bit_cast(x, as<uiT>()) >> 32;
        hx += 0x3ff00000 - 0x3fe6a09e;
        k += bit_cast(hx>>20, as<iT>()) - 0x3ff;
        hx = (bit_and(0x000fffffull, hx)) + 0x3fe6a09e;
        x = bit_cast(hx<<32 | (bit_and(0xffffffffull, bit_cast(x, as<uiT>()) )), as<T>());
        
        T f = dec(x);
        T s = f/(2.0f + f);
        T z = sqr(s);
        T w = sqr(z);
        T t1= w*horn<T, 0x3fd999999997fa04ull, 0x3fcc71c51d8e78afull, 0x3fc39a09d078c69full > (w);
        T t2= z*horn<T, 0x3fe5555555555593ull, 0x3fd2492494229359ull
          , 0x3fc7466496cb03deull, 0x3fc2f112df3e5244ull> (w);
        T R = t2 + t1;
        T hfsq = Half<T>()*sqr(f);
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
        T Invlog_2hi =  Ieee_constant<T, 0x3fb8b000U, 0x3ff7154765200000ULL>();
        T  hi = f - hfsq;
        hi =  bit_and(hi, (Allbits<uiT>() << 32));
        T lo = fma(s, hfsq+R, f - hi - hfsq);
        
        T val_hi = hi*Invlog_2hi;
        T val_lo = fma(lo+hi, Invlog_2lo, lo*Invlog_2hi);
        
        T dk = tofloat(k);
        T w1 = dk + val_hi;
        val_lo += (dk - w1) + val_hi;
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
  EVE_FORCEINLINE auto log2_(EVE_SUPPORTS(cpu_)
                            , plain_type const &  
                            , const T &a0) noexcept
  requires(T, vectorized<T>, behave_as<floating_point, T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::log2, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::log2, a0);
    else
    {
      if constexpr(std::is_same_v<value_type_t<T>, float>)
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
        
        T r =   fma(fms(s, hfsq+R, hfsq)+f, Invlog_2<T>(), dk);
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
        T Invlog_2hi =  Ieee_constant<T, 0x3fb8b000U, 0x3ff7154765200000ULL>();
        T  hi = f - hfsq;
        hi =  bit_and(hi, (Allbits<uiT>() << 32));
        T lo = fma(s, hfsq+R, f - hi - hfsq);
        
        T val_hi = hi*Invlog_2hi;
        T val_lo = fma(lo+hi, Invlog_2lo, lo*Invlog_2hi);
        
        T w1 = dk + val_hi;
        val_lo += (dk - w1) + val_hi;
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

