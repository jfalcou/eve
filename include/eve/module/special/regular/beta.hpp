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
//! @addtogroup special
//! @{
//!   @var beta
//!   @brief Computes the beta function: \f$\displaystyle \mathbf{B}(x, y) = \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$ is returned.
//!
//!   **Defined in header**
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
//!      template< eve::floating_ordered_value T, eve::floating_ordered_value U >
//!      auto beta(T x,U y) noexcept;
//!   @endcode
//!
//!   **Parameters**
//!
//!     `x`, `y`:  [strictly positive real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!     *  \f$\displaystyle \mathbf{B}(x,y) = \int_0^1 t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
//!
//!   @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/beta.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(beta_, beta);
}

#include <eve/module/special/regular/impl/beta.hpp>
