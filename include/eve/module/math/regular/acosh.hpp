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
#include <eve/module/math/constant/inv_2eps.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve
{
  template<typename Options>
  struct acosh_t : elementwise_callable<acosh_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(acosh_t, acosh_);
};

//================================================================================================
//! @addtogroup math_invhyper
//! @{
//! @var acosh
//! @brief `elementwise_callable` object computing  \f$\log(x+\sqrt{x^2-1})\f$.
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
//!      constexpr auto acosh(floating_value auto x)                         noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acosh[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto acosh[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`:  [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
//!      For values in the domain `x>1`, the inverse hyperbolic cosine is semantically equivalent to
//!      \f$\log(x+\sqrt{x^2-1})\f$.
//!      In particular:
//!      * If `x` is less than \f$1\f$ or `Nan`, `NaN` is returned.
//!      * If `x` is \f$1\f$, \f$+0\f$ is returned.
//!      * If `x` is \f$+\infty\f$, \f$+\infty\f$ is returned.
//!      * If `x` is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: acosh](https://en.cppreference.com/w/cpp/numeric/math/acosh)
//!   *  [Wolfram MathWorld: Inverse Hyperbolic Cosine](https://mathworld.wolfram.com/InverseHyperbolicCosine.html)
//!   *  [Wikipedia: Inverse hyperbolic functions](https://en.wikipedia.org/wiki/Inverse_hyperbolic_functions)
//!   *  [DLMF](https://dlmf.nist.gov/4.37)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acosh.cpp}
//!
//================================================================================================
  inline constexpr auto acosh = functor<acosh_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acosh_(EVE_REQUIRES(cpu_), O const&, T const& x)
    {
      const T    t    = dec(x);
      auto const test = is_greater(t, inv_2eps(eve::as<T>()));

      if constexpr( simd_value<T> )
      {
        const T z = if_else(test, x, t + sqrt(fma(t, t, t + t)));
        return add[test](log1p(z), log_2(eve::as<T>()));
      }
      else if constexpr( scalar_value<T> )
      {
        if( test ) { return eve::log(t) + log_2(eve::as<T>()); }
        else { return eve::log1p(t + eve::sqrt(fma(t, t, t + t))); }
      }
    }
  }
}
