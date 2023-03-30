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
//! @addtogroup core_bitops
//! @{
//!   @var bit_reverse
//!   @brief  elementwise reverse the bit order.
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
//!      template< eve::value T >
//!      T bit_reverse(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The values of the of the parameter are returned with bits in reversed order.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_reverse.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_reverse[mask](x, ...)` provides a masked
//!     version of `bit_reverse` which is
//!     equivalent to `if_else(mask, bit_reverse(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_reverse.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_reverse_, bit_reverse);
}

#include <eve/module/core/regular/impl/bit_reverse.hpp>
