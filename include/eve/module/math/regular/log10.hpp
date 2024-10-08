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
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve
{
  template<typename Options>
  struct log10_t : elementwise_callable<log10_t, Options>
  {
    template<floating_value T>
    EVE_FORCEINLINE  constexpr T operator()(T v) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(log10_t, log10_);
  };

  //================================================================================================
  //! @addtogroup math_log
  //! @{
  //! @var log10
  //!
  //! @brief `elementwise_callable` object computing the base 10  logarithm: \f$\log_{10} x\f$.
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
  //!      constexpr auto log10(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto log10[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto log10[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!    * `x`: [floating value](@ref eve::floating_value).
  //!    * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!    * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1.  Returns the [elementwise](@ref glossary_elementwise) the base 10 logarithm  of `x`
  //!      In particular, for floating inputs:
  //!        * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
  //!        * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!        * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
  //!        * If the element is less than 0, `NaN` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/log10)
  //!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/CommonLogarithm.html)
  //!   *  [Wikipedia](https://en.wikipedia.org/wiki/Logarithm)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/log10.cpp}
  //================================================================================================
  inline constexpr auto log10 = functor<log10_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    EVE_FORCEINLINE constexpr T
    log10_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      if constexpr(simd_value<T>)
      {
        if constexpr( has_native_abi_v<T> )
        {
          using uiT     = as_integer_t<T, unsigned>;
          using iT      = as_integer_t<T, signed>;
          using elt_t   = element_type_t<T>;
          constexpr bool is_avx = current_api == avx;
          using TT =  std::conditional_t<is_avx, T, iT >;
          T Invlog_10hi = ieee_constant<0x1.bcc0000p-2f, 0x1.bcb7b15200000p-2>(eve::as<T>{});
          T Invlog_10lo = ieee_constant<-0x1.09d5b20p-15f, 0x1.b9438ca9aadd5p-36>(eve::as<T>{});
          T Log10_2hi   = ieee_constant<0x1.3400000p-2f, 0x1.3440000000000p-2>(eve::as<T>{});
          T Log10_2lo   = ieee_constant<0x1.04d4280p-12f, 0x1.3509f79fef312p-18>(eve::as<T>{});
          if constexpr( std::is_same_v<elt_t, float> )
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
            T          x = a0;
            TT         k(0);
            T f(0);
            auto       isnez = is_nez(a0);
            logical<T> test;
            if constexpr( eve::platform::supports_denormals )
            {
              test = is_less(a0, smallestposval(eve::as<T>())) && isnez;
              if( eve::any(test) )
              {
                k = sub[test](k, TT(25));
                x = if_else(test, x * T(33554432ul), x);
              }
            }
            if constexpr(is_avx)
            {
              auto [xx, kk]     = eve::frexp(x);
              x = xx;
              auto x_lt_sqrthf = (invsqrt_2(eve::as<T>()) > x);
              k += dec[x_lt_sqrthf](kk);
              f    = dec(x + if_else(x_lt_sqrthf, x, eve::zero));
            }
            else
            {
              uiT ix = bit_cast(x, as<uiT>());
              /* reduce x into [sqrt(2)/2, sqrt(2)] */
              ix += 0x3f800000 - 0x3f3504f3;
              k += bit_cast(ix >> 23, as<iT>()) - 0x7f;
              ix       = (ix & 0x007fffff) + 0x3f3504f3;
              x        = bit_cast(ix, as<T>());
              f        = dec(x);
            }
            T s      = f / (2.0f + f);
            T z      = sqr(s);
            T w      = sqr(z);
            T t1     = w * eve::reverse_horner(w, T(0x1.999c26p-2f), T(0x1.f13c4cp-3f));
            T t2     = z * eve::reverse_horner(w, T(0x1.555554p-1f), T(0x1.23d3dcp-2f));
            T R      = t2 + t1;
            T hfsq   = half(eve::as<T>()) * sqr(f);
            T dk     = convert(k, as<float>());
            T hibits = f - hfsq;
            hibits   = bit_and(hibits, uiT(0xfffff000ul));
            T lobits = fma(s, hfsq + R, f - hibits - hfsq);
            //      T r = ((((dk*log10_2lo + (lobits+hibits)*ivln10lo) + lobits*ivln10hi) +
            //      hibits*ivln10hi) + dk*log10_2hi);
            T r = fma(dk,
                      Log10_2hi,
                      fma(hibits,
                          Invlog_10hi,
                          fma(lobits, Invlog_10hi, fma(lobits + hibits, Invlog_10lo, dk * Log10_2lo))));
            T zz;
            if constexpr( eve::platform::supports_infinites )
            {
              zz = if_else(isnez, if_else(a0 == inf(eve::as<T>()), inf(eve::as<T>()), r), minf(eve::as<T>()));
            }
            else { zz = if_else(isnez, r, minf(eve::as<T>())); }
            return if_else(is_ngez(a0), eve::allbits, zz);
          }
          else if constexpr( std::is_same_v<elt_t, double> )
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
            T          x = a0;
            TT         k(0);
            T          f(0);
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
            /* reduce x into [sqrt(2)/2, sqrt(2)] */
            if constexpr(is_avx)
            {
              auto [xx, kk]     = eve::frexp(x);
              x =  xx;
              auto x_lt_sqrthf = (invsqrt_2(eve::as<T>()) > x);
              k += dec[x_lt_sqrthf](kk);
              f  = dec(x + if_else(x_lt_sqrthf, x, eve::zero));
            }
            else
            {
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
            T t1 = w * eve::reverse_horner(w, T(0x1.999999997fa04p-2), T(0x1.c71c51d8e78afp-3), T(0x1.39a09d078c69fp-3));
            T t2 = z * eve::reverse_horner(w, T(0x1.5555555555593p-1), T(0x1.2492494229359p-2)
                                          , T(0x1.7466496cb03dep-3), T(0x1.2f112df3e5244p-3));
            T R    = t2 + t1;
            T hfsq = half(eve::as<T>()) * sqr(f);
            T dk   = convert(k, as<double>());
            //      T r = -(hfsq-(s*(hfsq+R))-f)*Invlog_10<T>()+dk*Log_2olog_10<T>(); // fast ?
            T hi     = f - hfsq;
            hi       = bit_and(hi, (allbits(eve::as<uiT>()) << 32));
            T lo     = f - hi - hfsq + s * (hfsq + R);
            T val_hi = hi * Invlog_10hi;
            T y      = dk * Log10_2hi;
            T val_lo = dk * Log10_2lo + (lo + hi) * Invlog_10lo + lo * Invlog_10hi;
            //
            //  Extra precision in for adding y is not strictly needed
            //  since there is no very large cancellation near x = sqrt(2) or
            //  x = 1/sqrt(2), but we do it anyway since it costs little on CPUs
            //  with some parallelism and it reduces the error for many args.
            //
            T w1 = y + val_hi;
            val_lo += (y - w1) + val_hi;
            val_hi = w1;

            T r = val_lo + val_hi;
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
        else return apply_over(log10, a0);
      }
      else  // scalar case
      {
        using uiT     = as_integer_t<T, unsigned>;
        using iT      = as_integer_t<T, signed>;
        T Invlog_10hi = ieee_constant<0x1.bcc0000p-2f, 0x1.bcb7b15200000p-2>(eve::as<T>{});
        T Invlog_10lo = ieee_constant<-0x1.09d5b20p-15f, 0x1.b9438ca9aadd5p-36>(eve::as<T>{});
        T Log10_2hi   = ieee_constant<0x1.3400000p-2f, 0x1.3440000000000p-2>(eve::as<T>{});
        T Log10_2lo   = ieee_constant<0x1.04d4280p-12f, 0x1.3509f79fef312p-18>(eve::as<T>{});
        if constexpr( std::is_same_v<T, float> )
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
          auto x = a0;
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
          T s    = f / (2.0f + f);
          T z    = sqr(s);
          T w    = sqr(z);
          T t1   = w * eve::reverse_horner(w, T(0x1.999c26p-2f), T(0x1.f13c4cp-3f));
          T t2   = z * eve::reverse_horner(w, T(0x1.555554p-1f), T(0x1.23d3dcp-2f));
          T R    = t2 + t1;
          T hfsq = 0.5f * sqr(f);
          //      return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<A0>()+k*Log_2olog_10<A0>(); // raw ?

          T hibits = f - hfsq;
          hibits   = bit_and(hibits, uiT(0xfffff000ul));
          T lobits = fma(s, hfsq + R, f - hibits - hfsq);
          T dk     = k;
          //      return ((((dk*Log10_2lo<T> + (lobits+hibits)*Invlog_10lo<T>()) +
          //      lobits*Invlog_10hi<T>()) + hibits*Invlog_10hi<T>()) + dk*Log10_2hi<T>());
          return fma(dk,
                     Log10_2hi,
                     fma(hibits,
                         Invlog_10hi,
                         fma(lobits, Invlog_10hi, fma(lobits + hibits, Invlog_10lo, dk * Log10_2lo))));
        }
        else if constexpr( std::is_same_v<T, double> )
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
          auto x = a0;
          uiT hx = bit_cast(x, as<uiT>()) >> 32;
          iT  k  = 0;
          if( hx < 0x00100000 || hx >> 31 )
          {
            if( is_eqz(x) ) return minf(eve::as<T>()); /* log(+-0)=-inf */
            if( hx >> 31 ) return nan(eve::as<T>());   /* log(-#) = NaN */
            /* subnormal number, scale x up */
            if constexpr( eve::platform::supports_denormals )
            {
              k -= 54;
              x *= 18014398509481984.0;
              hx = bit_cast(x, as<uiT>()) >> 32;
            }
          }
          else if( hx >= 0x7ff00000 ) return x;
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
          T t1   = w *eve::reverse_horner(w, T(0x1.999999997fa04p-2), T(0x1.c71c51d8e78afp-3)
                                         , T(0x1.39a09d078c69fp-3));
          T t2   = z* eve::reverse_horner(w, T(0x1.5555555555593p-1), T(0x1.2492494229359p-2)
                                         , T(0x1.7466496cb03dep-3), T(0x1.2f112df3e5244p-3));
          T R  = t2 + t1;
          T dk = k;
          //          return -(hfsq-(s*(hfsq+R))-f)*Invlog_10<T>()+dk*Log_2olog_10<T>(); //raw ?

          T hi     = f - hfsq;
          hi       = bit_and(hi, (allbits(eve::as<uiT>()) << 32));
          T lo     = f - hi - hfsq + s * (hfsq + R);
          T val_hi = hi * Invlog_10hi;
          T y      = dk * Log10_2hi;
          T val_lo = fma(dk, Log10_2lo, fma(lo + hi, Invlog_10lo, lo * Invlog_10hi));
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
    }
  }
}
