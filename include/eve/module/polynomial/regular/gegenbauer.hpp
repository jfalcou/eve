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
//!   @var gegenbauer
//!   @brief Computes the value of a  gegenbauer polynomial \f$ \mathbf{C}_n^\lambda(x)\f$.
//!
//!   The Gegenbauer polynomials are a sequence of orthogonal polynomials relative to
//!   \f$(1-x^2)^{\lambda-1/2\f$ on the \f$[-1, +1]\f$ interval satisfying the following
//!   recurrence relation:
//!     * \f$ \mathbf{C}_0^\lambda(x) = 1\f$.
//!     * \f$ \mathbf{C}_1^\lambda(x) = 2\lambda x\f$.
//!     * \f$ \mathbf{C}_n^\lambda(x) = \left[(2x+\lambda-1)\mathbf{C}_{n-1}^\lambda(x) -
//!           (n+2\lambda-2)\mathbf{C}_{n-2}^\lambda(x)\right]/n\f$.
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
//!     template< eve::integral_value T eve::floating_real_value T, eve::floating_real_value U >
//!     eve::as_wide_as<eve::common_compatible_value<T, U>, N>
//!     auto  gegenbauer(N n, T lambda, U x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integral argument](@ref eve::integral_value).
//!
//!     * `lambda` :  [real floating argument](@ref eve::floating_real_value).
//!                   Must be greater than \f$-\frac12\f$.
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value) .
//!
//!   **Return value**
//!
//!   The value of \f$ \mathbf{C}_n^\lambda(x)f$ is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/gegenbauer.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(gegenbauer_, gegenbauer);
}

#include <eve/module/polynomial/regular/impl/gegenbauer.hpp>
