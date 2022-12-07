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
//! @addtogroup special
//! @{
//!   @var betainc_inv
//!   @brief Computes the inverse relative to the first parameter of the beta incomplete function.
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
//!      template < eve::floating_ordered_value S
//!               , eve::floating_ordered_value T
//!               , eve::floating_ordered_value U>
//!      eve:common_value_t<S, T, U>  betainc_inv(S s, T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `s` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!     * `x`, `y`:  [strictly positive real floating arguments](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of inverse of incomplete beta function relative to the first parameter
//!   is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/betainc_inv.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(betainc_inv_, betainc_inv);
}

#include <eve/module/special/regular/impl/betainc_inv.hpp>
