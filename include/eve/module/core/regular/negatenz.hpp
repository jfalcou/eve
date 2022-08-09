//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negatenz
//!   @brief Computes the [elementwise](@ref glossary_elementwise) product of the first parameter
//!   by the never zero sign of the second.
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
//!      template< eve::value T, eve::value U >
//!      eve::common_compatible_t<T, U> negatenz(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!      The [elementwise](@ref glossary_elementwise) product of the first parameter
//!      by the never zero sign of the second is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/negatenz.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::negatenz[mask](x, ...)` provides a masked
//!     version of `negatenz` which is
//!     equivalent to `if_else(mask, negatenz(x, ...), x)`
//!      **Example**
//!
//!        @godbolt{doc/core/raw/negatenz.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(negatenz_, negatenz);
}

#include <eve/module/core/regular/impl/negatenz.hpp>
