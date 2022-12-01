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
//! @addtogroup elliptic
//! @{
//!   @var ellint_rj
//!   @brief Computes the Carlson's elliptic integral
//!   \f$ \mathbf{R}_\mathbf{J}(x, y) = \frac32 \int_{0}^{\infty}
//!   \scriptstyle(t+p)^{-1}[(t+x)(t+y)(t+z)]^{-1/2}\scriptstyle\;\mathrm{d}t\f$.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/elliptic.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_real_value T
//!              , eve::floating_real_value U
//!              , eve::floating_real_value V
//!              , eve::floating_real_value W>
//!      eve::common_value_t<T, U, V, W> ellint_rj(T x, U y, V z, W p) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`: [floating real arguments](@ref eve::floating_real_value). `x`, `y` and  `z`
//!                     must be non negative and at most one of them equal to 0. In any other case,
//!                     the result is NaN.
//!     * `p`:  Non-zero [floating real arguments](@ref eve::floating_real_value). In any other case,
//!             the result is NaN.
//!
//!   **Return value**
//!
//!   the value of the \f$\mathbf{R}_\mathbf{J}\f$ Carlson elliptic integral is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
EVE_MAKE_CALLABLE(ellint_rj_, ellint_rj);
}

#include <eve/module/elliptic/regular/impl/ellint_rj.hpp>
