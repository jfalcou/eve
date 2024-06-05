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
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/exp.hpp>

namespace eve
{
  template<typename Options>
  struct cosh_t : elementwise_callable<cosh_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cosh_t, cosh_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var cosh
//!
//! @brief Callable object computing \f$\frac{e^x+e^{-x}}2\f$.
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
//!      T cosh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) hyperbolic cosine of the input.
//!
//!      In particular:
//!
//!      * If the element is \f$\pm0\f$, 1 is returned.
//!      * If the element is \f$\pm\infty\f$, \f$+\infty\f$ is returned.
//!      * If the element is a `NaN`, `NaN` is returned.
//!
//!      * for every z: `eve::cosh(eve::conj(z)) == eve::conj(std::cosh(z))`
//!      * for every z: `eve::cosh(-z)           == eve::cosh(z)`
//!      *  If z is \f$0\f$, the result is \f$1\f$
//!      *  If z is \f$i \infty\f$, the result is \f$NaN\f$
//!      *  If z is \f$i NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$x+i \infty\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$x+i NaN\f$ (for any finite non-zero x), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$\infty+i 0\f$, the result is \f$\infty+i 0\f$
//!      *  If z is \f$\infty,y\f$ (for any finite non-zero y), the result is \f$\infty \mathrm{cis}\times(y)\f$
//!      *  If z is \f$\infty+i \infty\f$, the result is \f$\pm \infty+i NaN\f$  (the sign of the real part is unspecified)
//!      *  If z is \f$\infty+i NaN\f$, the result is \f$\infty+i NaN\f$
//!      *  If z is \f$NaN\f$, the result is \f$NaN\f$
//!      *  If z is \f$NaN+i y\f$ (for any finite non-zero y), the result is \f$NaN+i NaN\f$
//!      *  If z is \f$NaN+i NaN\f$, the result is \f$NaN+i NaN\f$
//!
//!      where \f$\mathrm{cis}(y) =  \cos(y)+i\sin(y)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cosh.cpp}
//!
//!
//!  @}
//================================================================================================
  inline constexpr auto cosh = functor<cosh_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cosh_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      //////////////////////////////////////////////////////////////////////////////
      // if x = abs(a0) according x < Threshold e =  exp(x) or exp(x/2) is
      // respectively computed
      // *  in the first case cosh (e+rec[pedantic2](e))/2
      // *  in the second     cosh is (e/2)*e (avoiding undue overflow)
      // Threshold is maxlog - Log_2
      //////////////////////////////////////////////////////////////////////////////
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return one(eve::as(a0));
      }
      T ovflimitmln2 = maxlog(as(a0))-log_2(as(a0));
      auto x = eve::abs(a0);
      if constexpr( scalar_value<T> )
      {
        if(is_not_finite(x)) return x;
        else if( x >= ovflimitmln2 )
        {
          auto w = exp(x * half(eve::as<T>()));
          auto t = half(eve::as<T>()) * w;
          t *= w;
          return t;
        }
        auto t = exp(x);
        return (x > 22) ? t * half(eve::as<T>()) : average(t, rec[pedantic2](t));
      }
      else
      {
        auto t    = exp(x);
        auto invt = if_else(x > 22, eve::zero, rec[pedantic2](t));
        auto c    = average(t, invt);
        auto test = x < ovflimitmln2;
        if( eve::all(test) ) return c;
        auto w = exp(x * half(eve::as<T>()));
        t      = half(eve::as<T>()) * w;
        t *= w;

        c = if_else(test, c, t);
        return c;
      }
    }
  }
}
