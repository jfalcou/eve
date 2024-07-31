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
//! @brief  `elementwise_callable` object computing the hyperbolic cosine: \f$\frac{e^x+e^{-x}}2\f$.
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
//!      constexpr auto cosh(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cosh[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cosh[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!   1.  Returns the [elementwise](@ref glossary_elementwise) hyperbolic cosine of the input.
//!       In particular:
//!        * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, \f$+\infty\f$ is returned.
//!        * If the element is a `NaN`, `NaN` is returned.
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/cosh)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/HyperbolicCosine.html)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Hyperbolic_functions)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/cosh.cpp}
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
