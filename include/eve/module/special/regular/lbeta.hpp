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
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct lbeta_t : elementwise_callable<lbeta_t, Options>
  {
    template<floating_value T0, floating_value T1>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 a, T1 b) const  noexcept
      requires (same_lanes_or_scalar<T0, T1>)
    {
      return this->behavior(as<common_value_t<T0, T1>>{}, eve::current_api, this->options(), a, b);
    }

    EVE_CALLABLE_OBJECT(lbeta_t, lbeta_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var lbeta
//!   @brief `elementwise_callable` object computing the natural logarithm of the beta function.
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
//!      constexpr auto lbeta(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto lbeta[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto lbeta[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [strictly positive real floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. the natural logarithm of the [beta](@ref beta) function.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [DLMF: Beta Function](https://dlmf.nist.gov/5.12)
//!   *  [C++ standard reference: beta](https://en.cppreference.com/w/cpp/numeric/special_functions/beta)
//!   *  [Wolfram MathWorld: Beta Function](https://mathworld.wolfram.com/LaguerrePolynomial.html)https://mathworld.wolfram.com/BetaFunction.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/special/lbeta.cpp}
//================================================================================================
 inline constexpr auto lbeta = functor<lbeta_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template< typename T, callable_options O>
    constexpr EVE_FORCEINLINE auto lbeta_(EVE_REQUIRES(cpu_), O const&, T a0, T a1)
    {
      return log_abs_gamma(a0) + log_abs_gamma(a1) - log_abs_gamma(a0 + a1);
    }
  }
}
