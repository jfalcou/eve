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
#include <eve/module/math/regular/asin.hpp>

namespace eve
{
  template<typename Options>
  struct acsc_t : elementwise_callable<acsc_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(acsc_t, acsc_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acsc
//!   @brief Callable object computing the arc cosecant.
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
//!      constexpr auto acsc(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acsc[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto acsc[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
//!      input in the range \f$[-\pi/2 , \pi/2]\f$.
//!      In particular:
//!      * If the element is \f$\pm1\f$, \f$\pm\frac\pi2\f$ is returned.
//!      * If the element \f$|x| < 1\f$, `NaN` is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Cosecant](https://mathworld.wolfram.com/InverseCosecant.html)
//!   *  [Wikipedia: Inverse trigonometricfunctions](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions)
//!   *  [DLMF](https://dlmf.nist.gov/4.23)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acsc.cpp}
//================================================================================================
  inline constexpr auto acsc = functor<acsc_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acsc_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return eve::asin(rec[pedantic](a));
    }
  }
}
