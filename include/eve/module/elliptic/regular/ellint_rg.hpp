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
//!   @var ellint_rg
//!   @brief Computes the Carlson's elliptic integral
//!   \f$ \mathbf{R}_\mathbf{G}(x, y) = \frac1{4\pi} \int_{0}^{2\pi}\int_{0}^{\pi}
//!   \scriptstyle\sqrt{x\sin^2\theta\cos^2\phi
//!   +y\sin^2\theta\sin^2\phi
//!   +z\cos^2\theta} \scriptstyle\;\mathrm{d}\theta\;\mathrm{d}\phi\f$
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
//!      template< eve::floating_ordered_value T
//!              , eve::floating_ordered_value U
//!              , eve::floating_ordered_value V >
//!      eve::common_value_t<T, U, V> ellint_rg(T x, U y, V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`:  [floating real arguments](@ref eve::floating_ordered_value).
//!                       All arguments must be non-negative or the result is nan.
//!
//!   **Return value**
//!
//!   the value of the \f$\mathbf{R}_\mathbf{G}\f$ Carlson elliptic integral is returned:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(ellint_rg_, ellint_rg);
}

#include <eve/module/elliptic/regular/impl/ellint_rg.hpp>
