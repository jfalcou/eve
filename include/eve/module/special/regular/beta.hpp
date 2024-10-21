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
#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/module/special/regular/signgam.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct beta_t : elementwise_callable<beta_t, Options>
  {
    template<floating_value T0, floating_value T1>
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
      requires (same_lanes_or_scalar<T0, T1>)
    {
      return this->behavior(as<common_value_t<T0, T1>>{}, eve::current_api, this->options(), a, b);
    }

    EVE_CALLABLE_OBJECT(beta_t, beta_);
  };

  //================================================================================================
  //! @addtogroup special
  //! @{
  //!   @var beta
  //!   @brief `elementwise_callable` object computing the beta function: \f$\displaystyle \mathbf{B}(x, y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$.
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
  //!      constexpr auto beta(floating_value auto x, floating_value auto y)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto beta[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
  //!      constexpr auto beta[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`: [strictly positive real floating argument](@ref eve::floating_value).
  //!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!     * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //!   **Return value**
  //!
  //!     1. \f$\displaystyle \mathbf{B}(x,y) = \int_0^1 t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
  //!     2. [The operation is performed conditionnaly](@ref conditional).
  //!
  //!  @groupheader{External references}
  //!   *  [DLMF: Beta Function](https://dlmf.nist.gov/5.12)
  //!   *  [C++ standard reference: beta](https://en.cppreference.com/w/cpp/numeric/special_functions/beta)
  //!   *  [Wolfram MathWorld: Beta Function](https://mathworld.wolfram.com/LaguerrePolynomial.html)https://mathworld.wolfram.com/BetaFunction.html)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/special/beta.cpp}
  //================================================================================================
  inline constexpr auto beta = functor<beta_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T beta_(EVE_REQUIRES(cpu_), O const&, T a0, T a1) noexcept
    {
      auto y    = a0 + a1;
      auto sign = eve::signgam(a0) * eve::signgam(a1) * eve::signgam(y);
      return sign * exp(log_abs_gamma(a0) + log_abs_gamma(a1) - log_abs_gamma(y));
    }
  }
}
