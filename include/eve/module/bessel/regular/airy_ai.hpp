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

namespace eve
{
  template<typename Options>
  struct airy_ai_t : elementwise_callable<airy_ai_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(airy_ai_t, airy_ai_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var airy_ai
//!   @brief `elementwise_callable` object computing the airy function \f$ Ai(x)\f$.
//!
//!   It is the solution of the differential equation \f$y''-xy = 0\f$ satisfying
//!   \f$Ai(0) = \frac1{3^{2/3}\Gamma(2/3)}\f$ and \f$Ai'(0) =\frac1{3^{1/3}\Gamma(1/3)}\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/bessel.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto airy_ai(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto airy_ai[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto airy_ai[logical_value auto m](floating_value auto x)    noexcept; // 2.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   * `x` :  [floating value](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!      1. The value of \f$ \displaystyle Ai(x)=\frac1{\pi} \int_{0}^{\infty}\cos
//!      \left( \frac{t^3}{3}+xt \right) \,dt\f$ is returned.
//!      2. [The operation is performed conditionnaly.](@ref conditional).
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/regular/airy_ai.cpp}
//! @}
//================================================================================================
  inline constexpr auto airy_ai = functor<airy_ai_t>;
}

#include <eve/module/bessel/regular/impl/airy_ai.hpp>
