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
//!   @var lbeta
//!   @brief Computes the natural logarithm of the beta function.
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
//!      auto lbeta(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     `x`, `y`:  [strictly positive real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!  @godbolt{doc/special/regular/lbeta.cpp}
//!
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lbeta_, lbeta);
}

#include <eve/module/special/regular/impl/lbeta.hpp>
