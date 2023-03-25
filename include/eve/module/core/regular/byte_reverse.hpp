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
//!   @var byte_reverse
//!   @brief reverses the byte order.
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
//!      T byte_reverse(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The values of the of the parameter are returned with bytes in reversed order.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/byte_reverse.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::byte_reverse[mask](x, ...)` provides a masked
//!     version of `byte_reverse` which is
//!     equivalent to `if_else(mask, byte_reverse(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/byte_reverse.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(byte_reverse_, byte_reverse);
}

#include <eve/module/core/regular/impl/byte_reverse.hpp>
