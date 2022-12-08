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
//!   @var betainc
//!   @brief Computes the beta incomplete function. \f$\displaystyle \mbox{I}_s(x,y) =
//!   \frac{1}{\mbox{B}(x,y)}\int_0^s t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
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
//!      template< eve::floating_ordered_value S
//!              , eve::floating_ordered_value T
//!              , eve::floating_ordered_value U>
//!      eve:common_value_t<S, T, U>  $name$(S s, T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `s` :  [real floating argument](@ref eve::floating_ordered_value). \f$ s \in [0, 1]\f$
//!
//!     * `x`, `y`:  [strictly positive real floating arguments](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the incomplete beta function is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/betainc.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(betainc_, betainc);
}

#include <eve/module/special/regular/impl/betainc.hpp>
