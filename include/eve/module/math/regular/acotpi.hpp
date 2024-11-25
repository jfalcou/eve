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
#include <eve/module/math/detail/generic/atan_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct acotpi_t : elementwise_callable<acotpi_t, Options>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(acotpi_t, acotpi_);
};

//================================================================================================
//! @addtogroup math_invtrig
//! @{
//!   @var acotpi
//!   @brief Callable object computing te arc cotangent in \f$\pi\f$ multiples.
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
//!      constexpr auto acotpi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto acotpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto acotpi[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) value in \f$\pi\f$ multiples
//!      of the arc cotangent of the input in the range \f$]-\frac12, \frac12]\f$.
//!      In particular:
//!      * If the element is \f$\pm0\f$, \f$\pm\frac12\f$ is returned.
//!      * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!      * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Inverse Cotangent](https://mathworld.wolfram.com/InverseCotangent.html)
//!   *  [DLMF: ](https://dlmf.nist.gov/4.23.6)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/acotpi.cpp}
//================================================================================================
  inline constexpr auto acotpi = functor<acotpi_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T acotpi_(EVE_REQUIRES(cpu_), O const&, T const& a)
    {
      return radinpi(acot(a));
    }
  }
}
