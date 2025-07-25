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
#include <eve/module/special/regular/polygamma.hpp>

namespace eve
{
template<typename Options>
struct trigamma_t : elementwise_callable<trigamma_t, Options>
{
  template<eve::floating_value T>
  constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(trigamma_t, trigamma_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var trigamma
//!   @brief `elementwise_callable` object computing the Trigamma function i.e.
//!   the second derivative of the \f$\log\Gamma\f$  function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto trigamma(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto trigamma[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto trigamma[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [floating_value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the Trigamma function: \f$\psi(x) = \frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Gamma and Psi Functions](https://dlmf.nist.gov/5.2#i)
//!   *  [Wolfram MathWorld: Trigamma Function](https://mathworld.wolfram.com/TrigammaFunction.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/trigamma.cpp}
//================================================================================================
  inline constexpr auto trigamma = functor<trigamma_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr T  trigamma_(EVE_REQUIRES(cpu_), O const&, T z) noexcept
    {
      return polygamma(1, z);
    }
  }
}
