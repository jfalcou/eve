//======================================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/reverse_horner.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/constant/maxlog.hpp>

namespace eve
{
  template<typename Options>
  struct expm1_t : elementwise_callable<expm1_t, Options, pedantic_option>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(expm1_t, expm1_);
  };
//======================================================================================================================
//! @addtogroup math_exp
//! @{
//! @var expm1
//! @brief Callable object computing \f$e^x-1\f$.
//!
//!   @groupheader{Header file}
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
//!      constexpr auto expm1(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto expm1[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto expm1[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`: [value](@ref value).
//!    * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) exponential of `x-1`, with good
//!      accuracy, even for small values of `x`. In particular:
//!        * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned
//!        * If the element is \f$-\infty\f$, \f$-1\f$ is returned
//!        * If the element is \f$\infty\f$, \f$\infty\f$ is returned
//!        * If the element is a `NaN`, `NaN` is returned
//!    2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math//expm1.cpp}
//================================================================================================
  inline constexpr auto expm1 = functor<expm1_t>;
//================================================================================================
//!  @}
//======================================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    T  expm1_(EVE_REQUIRES(cpu_), O const& o, T const& xx)
    {
      using elt_t       = element_type_t<T>;
      using i_t         = as_integer_t<T>;
      const T Log_2hi   = ieee_constant<0x1.6300000p-1f, 0x1.62e42fee00000p-1>(eve::as<T>{});
      const T Log_2lo   = ieee_constant<-0x1.bd01060p-13f, 0x1.a39ef35793c76p-33>(eve::as<T>{});
      const T Invlog_2  = ieee_constant<0x1.7154760p+0f, 0x1.71547652b82fep+0>(eve::as<T>{});
      T       k         = nearest(Invlog_2 * xx);
      auto    xlelogeps = xx <= logeps(eve::as(xx));
      auto    xgemaxlog = xx >= maxlog(eve::as(xx));

      if constexpr( scalar_value<T> )
      {
        if( is_eqz(xx) || is_nan(xx) ) return xx;
        if( xgemaxlog ) return inf(eve::as<T>());
        if( xlelogeps ) return mone(eve::as<T>());
      }
      if constexpr( std::is_same_v<elt_t, float> )
      {
        T x    = fnma(k, Log_2hi, xx);
        x      = fnma(k, Log_2lo, x);
        T hx   = x * half(eve::as<T>());
        T hxs  = x * hx;
        T r1   = eve::reverse_horner(hxs, T(0x1.000000p+0f), T(-0x1.1110fep-5f), T(0x1.9edb68p-10f));
        T t    = fnma(r1, hx, T(3));
        T e    = hxs * ((r1 - t) / (T(6) - x * t));
        e      = fms(x, e, hxs);
        i_t ik = convert(k, int_from<T>());
        T   two2mk = bit_cast((maxexponent(eve::as<T>()) - ik) << nbmantissabits(eve::as<elt_t>()), as<T>());
        k = oneminus(two2mk) - (e - x);
        k = ldexp[o](k, ik);
      }
      else if constexpr( std::is_same_v<elt_t, double> )
      {
        T hi   = fnma(k, Log_2hi, xx);
        T lo   = k * Log_2lo;
        T x    = hi - lo;
        T hxs  = sqr(x) * half(eve::as<T>());
        T r1   = eve::reverse_horner(hxs, T(0x1.0000000000000p+0), T(-0x1.11111111110f4p-5), T(0x1.a01a019fe5585p-10)
                                    , T(-0x1.4ce199eaadbb7p-14), T(0x1.0cfca86e65239p-18), T(-0x1.afdb76e09c32dp-23)
                                    );
        T t    = T(3) - r1 * half(eve::as<T>()) * x;
        T e    = hxs * ((r1 - t) / (T(6) - x * t));
        T c    = (hi - x) - lo;
        e      = (x * (e - c) - c) - hxs;
        i_t ik = convert(k, int_from<T>());
        T   two2mk = bit_cast((maxexponent(eve::as<T>()) - ik) << nbmantissabits(eve::as<T>()), as<T>());
        T ct1 = oneminus(two2mk) - (e - x);
        T ct2 = inc((x - (e + two2mk)));
        k     = if_else((k < T(20)), ct1, ct2);
        k = ldexp[o](k, ik);
      }
      if constexpr( simd_value<T> )
      {
        k = if_else(xgemaxlog, inf(eve::as<T>()), k);
        k = if_else(is_eqz(xx) || is_nan(xx), xx, k);
        k = if_else(xlelogeps, eve::mone, k);
      }
      return k;
    }
  }
}
