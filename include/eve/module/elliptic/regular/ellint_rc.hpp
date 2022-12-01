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
//!   @var ellint_rc
//!   @brief computes the degenerate Carlson's elliptic integral
//!   \f$  \mathbf{R}_\mathbf{C}(x, y) = \frac12 \int_{0}^{\infty}
//!   \scriptstyle(t+x)^{-1/2}(t+y)^{-1}\scriptstyle\;\mathrm{d}t\f$.
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
//!      template< eve::floating_real_value T,  eve::floating_real_value U >
//!      eve::common_value_t<T, U> ellint_rc(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating real arguments](@ref eve::floating_real_value). `x` and `y` must be
//!                 strictly positive and `y` non zero or the result is NaN.
//!
//!   **Return value**
//!
//!    the value of the \f$\mathbf{R}_\mathbf{C}\f$ elliptic integral is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(ellint_rc_, ellint_rc);
}

#include <eve/module/elliptic/regular/impl/ellint_rc.hpp>
