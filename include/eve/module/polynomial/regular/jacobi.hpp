//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup polynomial
//! @{
//!   @var jacobi
//!   @brief Computes the value of the Jacobi polynomials \f$P^{\alpha, \beta}_n(x)\f$.
//!
//!   The Jacobi  polynomials are a sequence of orthogonal polynomials relative
//!   to \f$(1-x)^{\alpha}(1+x)^{\beta}\f$, for \f$\alpha \f$ and \f$\beta \f$ greater than -1,
//!   on the \f$[-1, +1]\f$ interval.
//!
//!   They can be defined via a Rodrigues formula:
//!    \f$\displaystyle P^{\alpha, \beta}_n(x) = \frac{(-1)^n}{2^n n!}(1-x)^{-\alpha}
//!    (1+x)^{-\beta} \frac{d}{dx^n}\left\{ (1-x)^{\alpha}(1+x)^{\beta}(1-x^2)^n \right\}\f$.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/polynomial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< eve::integral_value N
//!             , eve::floating_real_value T
//!             , eve::floating_real_value A
//!             , eve::floating_real_value B>
//!      eve::as_wide_as<common_compatible_value<T, A, B>, N>
//!      jacobi(N n, T x, A alpha,  B beta) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral positive argument](@ref eve::integral_value).
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!     * `alpha`, `beta`:   [floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!   The value of the polynomial \f$P^{\alpha, \beta}_n(x)\f$ is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/polynomial/regular/jacobi.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(jacobi_, jacobi);
}

#include <eve/module/polynomial/regular/impl/jacobi.hpp>
