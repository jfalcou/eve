//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
//!              , eve::floating_real_value X>
//!      eve::common_compatible_value<T, U, V, W> ellint_rj(T x, U y, V z, W p) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   `x`, `y`, `z` `p`:   [floating real arguments](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!     * the value of the \f$\mathbf{R}_\mathbf{J}\f$ Carlson elliptic integral is returned:
//!
//!   **Notes**
//!
//!     - `x`, `y` and  `z` must be non negative at most one of them 0.
//!     - `p`  must be non zero.
//!     - In any other case the result is nan.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
EVE_MAKE_CALLABLE(ellint_rj_, ellint_rj);
}

#include <eve/module/elliptic/regular/impl/ellint_rj.hpp>
