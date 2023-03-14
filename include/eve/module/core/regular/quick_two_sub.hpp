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
//! @subtogroup core_accuracy
//! @{
//!   @var two_sub
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  sum and error,
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T, eve::floating_value U  >
//!      kumi::tuple<T, T> quick_two_sub(T x, T y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, 'y':  [ordered floating arguments](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x-y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\ominus\f$`y`
//!
//!
//! where \f$\oplus\f$ subs its two parameters with infinite precision.
//!
//! @warning    Assumes |x| >= |y|
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/quick_two_sub.cpp}
//!
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(quick_two_sub_, quick_two_sub);
}

#include <eve/module/core/regular/impl/quick_two_sub.hpp>
