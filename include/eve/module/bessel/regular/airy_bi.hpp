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
  struct airy_bi_t : elementwise_callable<airy_bi_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(airy_bi_t, airy_bi_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var airy_bi
//!   @brief `elementwise_callable` object computing the airy function \f$ Bi(x)\f$.
//!
//!  It is the solution of the differential equation \f$y''-xy = 0\f$ satisfying
//!  \f$Ai(0) = \frac1{3^{1/6}\Gamma(2/3)}\f$ and
//!  \f$Ai'(0) =\frac{3^{1/6}}{\Gamma(1/3)}\f$.
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
//!      constexpr auto airy_bi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto airy_bi[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto airy_bi[logical_value auto m](floating_value auto x)    noexcept; // 2.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: positive [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!    1. The value of \f$ \displaystyle Bi(x) = \frac1{\pi}\int_{0}^{\infty}
//!      \left[\exp\left(-{\frac{t^{3}}{3}}+xt\right)+
//!      \sin\left({\frac{t^{3}}{3}}+xt\right)\,\right]dt\f$
//!      is returned.
//!    2. [The operation is performed conditionnaly.](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/AiryFunctions.html)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Airy_function)
//!   *  [DLMF](https://dlmf.nist.gov/9)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/regular/airy_bi.cpp}
//! @}
//================================================================================================
  inline constexpr auto airy_bi = functor<airy_bi_t>;
}

#include <eve/module/bessel/regular/impl/airy_bi.hpp>
