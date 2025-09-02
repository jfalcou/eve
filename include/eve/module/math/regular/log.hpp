//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/horner.hpp>
#include <eve/module/math/constant/invsqrt_2.hpp>

namespace eve
{

  template<typename Options>
  struct log_t : elementwise_callable<log_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log_t, log_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var log
//! @brief `elementwise_callable` object computing the natural logarithm: \f$\log x\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto log(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto log[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto log[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1.  Returns the [elementwise](@ref glossary_elementwise) the natural
//!      logarithm  of `x`: \f$\log x\f$.
//!        * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
//!        * If the element is \f$1\f$, \f$+0\f$ is returned.
//!        * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
//!        * If the element is less than 0, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/log)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/NaturalLogarithm.html)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Logarithm)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/log.cpp}
//================================================================================================
  inline constexpr auto log = functor<log_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T
    log_(EVE_REQUIRES(cpu_), O const &, T a0) noexcept
    {
      if constexpr(simd_value<T>)
      {
        using iT    = as_integer_t<T, signed>;
        constexpr bool is_avx = current_api == avx;
        using TT =  detail::conditional_t<is_avx, T, iT >;
        T Log_2hi   = ieee_constant<0x1.6300000p-1f, 0x1.62e42fee00000p-1>(eve::as<T>{});
        T Log_2lo   = ieee_constant<-0x1.bd01060p-13f, 0x1.a39ef35793c76p-33>(eve::as<T>{});
        using uiT   = as_integer_t<T, unsigned>;
        using elt_t = element_type_t<T>;
        if constexpr( std::is_same_v<elt_t, float> )
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
          auto       x = a0;
          T          f(0);
          TT         k(0);
          auto       isnez = is_nez(a0);
          logical<T> test;
          if constexpr( eve::platform::supports_denormals )
          {
            test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
            if( eve::any(test) )
            {
              k = sub[test](k, TT(23));
              x = if_else(test, x * T(8388608ul), x);
            }
          }
          if constexpr(is_avx)
          {
            auto [xx, kk]     = eve::frexp(x);
            x = xx;
            auto x_lt_sqrthf = (invsqrt_2(eve::as<T>()) > x);
            k += dec[x_lt_sqrthf](kk);
            f = dec(x + if_else(x_lt_sqrthf, x, eve::zero));
          }
          else
          {
            uiT ix = bit_cast(x, as<uiT>());
            /* reduce x into [sqrt(2)/2, sqrt(2)] */
            ix += 0x3f800000 - 0x3f3504f3;
            k += bit_cast(ix >> 23, as<iT>()) - 0x7f;
            ix     = (ix & 0x007fffff) + 0x3f3504f3;
            x      = bit_cast(ix, as<T>());
            f    = dec(x);
          }
          T s    = f / (2.0f + f);
          T z    = sqr(s);
          T w    = sqr(z);
          T t1   = w * eve::reverse_horner(w, T(0x1.999c26p-2f), T(0x1.f13c4cp-3f));
          T t2   = z * eve::reverse_horner(w, T(0x1.555554p-1f), T(0x1.23d3dcp-2f));
          T R    = t2 + t1;
          T hfsq = half(eve::as<T>()) * sqr(f);
          T dk = convert(k, as<float>());
          T r  = fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
          T zz;
          if constexpr( eve::platform::supports_infinites )
            zz = if_else(isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
          else
            zz = if_else(isnez, r, minf(eve::as<T>()));
          return if_else(is_ngez(a0), eve::allbits, zz);
        }
        else // if constexpr(std::is_same_v<elt_t, double>)
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
          auto x = a0;
          T f(0);
          TT         k(0);
          auto       isnez = is_nez(a0);
          logical<T> test;
          if constexpr( eve::platform::supports_denormals )
          {
            test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
            if( eve::any(test) )
            {
              k = sub[test](k, TT(54));
              x = if_else(test, x * T(18014398509481984ull), x);
            }
          }
          if constexpr(is_avx)
          {
            auto [xx, kk]     = eve::frexp(x);
            x = xx;
            auto x_lt_sqrthf = (invsqrt_2(eve::as<T>()) > x);
            k += dec[x_lt_sqrthf](kk);
            f  = dec(x + if_else(x_lt_sqrthf, x, eve::zero));
          }
          else
          {  /* reduce x into [sqrt(2)/2, sqrt(2)] */
            uiT hx = bit_cast(x, as<uiT>()) >> 32;
            hx += 0x3ff00000 - 0x3fe6a09e;
            k += bit_cast(hx >> 20, as<iT>()) - 0x3ff;
            hx = (bit_and(hx, 0x000fffffull)) + 0x3fe6a09e;
            x  = bit_cast(hx << 32 | (bit_and(bit_cast(x, as<uiT>()), 0xffffffffull)), as<T>());
            f  = dec(x);
          }
          T s  = f / (2.0f + f);
          T z  = sqr(s);
          T w  = sqr(z);
          T t1 = w*eve::reverse_horner(w, T(0x1.999999997fa04p-2), T(0x1.c71c51d8e78afp-3), T(0x1.39a09d078c69fp-3));
          T t2 = z*eve::reverse_horner(w, T(0x1.5555555555593p-1), T(0x1.2492494229359p-2)
                                      , T(0x1.7466496cb03dep-3), T(0x1.2f112df3e5244p-3));
          T R    = t2 + t1;
          T hfsq = half(eve::as<T>()) * sqr(f);

          T dk = convert(k, as<double>());
          T r  = fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
          T zz;
          if constexpr( eve::platform::supports_infinites )
          {
            zz = if_else(
              isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
          }
          else { zz = if_else(isnez, r, minf(eve::as<T>())); }
          return if_else(is_ngez(a0), eve::allbits, zz);
        }
      }
      else // scalar case
      {
        using uiT = as_integer_t<T, unsigned>;
        using iT  = as_integer_t<T, signed>;
        T Log_2hi = ieee_constant<0x1.6300000p-1f, 0x1.62e42fee00000p-1>(eve::as<T>{});
        T Log_2lo = ieee_constant<-0x1.bd01060p-13f, 0x1.a39ef35793c76p-33>(eve::as<T>{});
        auto x = a0;
        if constexpr( std::is_same_v<T, float> )
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
          uiT ix = bit_cast(x, as<uiT>());
          iT  k  = 0;
          if( ix < 0x00800000 || ix >> 31 ) /* x < 2**-126  */
          {
            if( ix << 1 == 0 ) return minf(eve::as<T>()); /* log(+-0)=-inf */
            if( ix >> 31 ) return nan(eve::as<T>());      /* log(-#) = NaN */
            if constexpr( eve::platform::supports_denormals )
            { /* subnormal number, scale up x */
              k -= 25;
              x *= 33554432.0f;
              ix = bit_cast(x, as<iT>());
            }
          }
          else if( ix >= 0x7f800000 ) { return x; }
          else if( ix == 0x3f800000 ) return zero(eve::as(x));
          /* reduce x into [sqrt(2)/2, sqrt(2)] */
          ix += 0x3f800000 - 0x3f3504f3;
          k += bit_cast(ix >> 23, as<iT>()) - 0x7f;
          ix     = (ix & 0x007fffff) + 0x3f3504f3;
          x      = bit_cast(ix, as<T>());
          T f    = dec(x);
          T s    = f/(2.0f + f);
          T z    = sqr(s);
          T w    = sqr(z);
          T t1   = w*eve::reverse_horner(w, T(0x1.999c26p-2f), T(0x1.f13c4cp-3f));
          T t2   = z*eve::reverse_horner(w, T(0x1.555554p-1f), T(0x1.23d3dcp-2f));
          T R    = t2 + t1;
          T hfsq = 0.5f * sqr(f);
          T dk   = convert(k, as<float>());
          return fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
        }
        else if constexpr( std::is_same_v<T, double> )
        {
          /* origin: FreeBSD /usr/src/lib/msun/src/e_log.c */
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
            if( is_eqz(x) ) return minf(eve::as<T>()); /* log(+-0)=-inf */
            if( hx >> 31 ) return nan(eve::as<T>());   /* log(-#) = NaN */
            if constexpr( eve::platform::supports_denormals )   /* subnormal number, scale x up */
            {
              k -= 54;
              x *= 18014398509481984.0;
              hx = bit_cast(x, as<uiT>()) >> 32;
            }
          }
          else if( hx >= 0x7ff00000 ) { return x; }
          else if( x == one(eve::as<T>()) ) return zero(eve::as<T>());
          /* reduce x into [sqrt(2)/2, sqrt(2)] */
          hx += 0x3ff00000 - 0x3fe6a09e;
          k += bit_cast(hx >> 20, as<iT>()) - 0x3ff;
          hx  = (hx & 0x000fffff) + 0x3fe6a09e;
          x   = bit_cast((uint64_t)hx << 32 | (bit_and(0xffffffffull, bit_cast(x, as<uiT>()))), as<T>());
          T f = dec(x);
          T hfsq = 0.5 * sqr(f);
          T s    = f / (2.0f + f);
          T z    = sqr(s);
          T w    = sqr(z);
          T t1   = w*eve::reverse_horner(w, T(0x1.999999997fa04p-2), T(0x1.c71c51d8e78afp-3), T(0x1.39a09d078c69fp-3));
          T t2   = z*eve::reverse_horner(w, T(0x1.5555555555593p-1), T(0x1.2492494229359p-2)
                                        , T(0x1.7466496cb03dep-3), T(0x1.2f112df3e5244p-3));
          T R  = t2 + t1;
          T dk = convert(k, as<double>());
          return fma(dk, Log_2hi, ((fma(s, (hfsq + R), dk * Log_2lo) - hfsq) + f));
        }
      }
    }
  }
}
