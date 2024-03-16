//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/constant/maxlog.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/expm1.hpp>

namespace eve
{
  template<typename Options>
  struct sinh_t : elementwise_callable<sinh_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sinh_t, sinh_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var sinh
//!
//! @brief Callable object computing \f$\frac{e^x-e^{-x}}2\f$.
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
//!      template< eve::floating_value T >
//!      T sinh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) hyperbolic sine of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!      * for every z: `eve::sinh(eve::conj(z)) == eve::conj(std::sinh(z))`
//!      * for every z: `eve::sinh(-z)           == -eve::sinh(z)`
//!      * If z is \f$+0\f$, the result is \f$+0\f$
//!      * If z is \f$i \infty\f$, the result is \f$i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$i NaN\f$, the result is \f$NaN\f$
//!      * If z is \f$x+i \infty\f$ (for any positive finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$x+i NaN\f$ (for any positive finite x), the result is \f$NaN+i NaN\f$
//!      * If z is \f$+\infty\f$, the result is \f$+\infty\f$
//!      * If z is \f$+\infty+i y\f$ (for any positive finite y), the result is \f$\infty\times cis(y)\f$
//!      * If z is \f$+\infty+i \infty\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$+\infty+i NaN\f$, the result is \f$\pm \infty+i NaN\f$ (the sign of the real part is unspecified)
//!      * If z is \f$NaN\f$, the result is \f$NaN\f$
//!      * If z is \f$NaN+i y\f$ (for any finite nonzero y), the result is \f$NaN+i NaN\f$
//!
//!      where \f$\mathrm{cis}(y) =  \cos(y)+i\sin(y)\f$
//!
//!  @godbolt{doc/math/regular/sinh.cpp}
//!
//!
//!  @}
//================================================================================================
  inline constexpr auto sinh = functor<sinh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sinh_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return a0;
      }
      else
      {
        T x = eve::abs(a0);

        if constexpr( scalar_value<T> )
        {
          T h = (a0 > T(0)) ? T(1) : T(-1);
          if( x >= maxlog(as<T>()) )
          {
            T w = exp(x * half(eve::as<T>()));
            T t = half(eve::as<T>()) * w;
            t *= w;
            return t * h;
          }
          h *= half(eve::as<T>());
          T t    = expm1(x);
          T inct = inc(t);
          T u    = t / inct;
          T s    = h * (fnma(t, u, t) + t);
          return s;
        }
        else
        {
          auto h    = if_else(is_gtz(a0), one(eve::as<T>()), mone);
          auto t    = expm1(x);
          auto inct = inc(t);
          auto u    = t / inct;
          auto z    = fnma(t, u, t);
          auto s    = half(eve::as<T>()) * h * (z + t);

          s         = if_else(is_eqz(a0), a0, s);
          auto test = x < maxlog(as<T>());
          if( eve::all(test) ) return s;
          auto w = exp(x * half(eve::as<T>()));
          t      = half(eve::as<T>()) * w;
          t *= w;

          return if_else(test, s, t * h);
        }
      }
    }
  }
}
