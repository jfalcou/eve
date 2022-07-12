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
//!   @var ellint_rd
//!   @brief Computes the Carlson's elliptic integral
//!   \f$  \mathbf{R}_\mathbf{D}(x, y) = \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2}
//!   (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.
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
//!              , eve::floating_real_value V >
//!      eve::common_compatible_value<T, U, V> ellint_rc(T x, U y, V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   `x`, `y`, `z`:   [floating real arguments](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!     * the value of the \f$\mathbf{R}_\mathbf{D}\f$ Carlson elliptic integral is returned:
//!
//!   **Notes**
//!
//!     - `x` and `y` must be strictly positive and `y` non zero.
//!     - `z` must be greater than 0.
//!     - In any other case the result is nan.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(ellint_rd_, ellint_rd);
}

#include <eve/module/elliptic/regular/impl/ellint_rd.hpp>
