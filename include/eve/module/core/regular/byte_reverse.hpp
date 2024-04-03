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
//!   @brief elementwise reverses the byte order.
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
//!    The values of the parameter elements are returned with bytes in reversed order.
//!
//!   @note eve::byte_reverse is the functional equivalent to std::byte_swap.
//!   However, we decided to name it byte_reverse in order to keep a proper naming
//!   scheme aligned with the eve::bit_swap/eve::bit_reverse functions.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/byte_reverse.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::byte_reverse[mask](x, ...)` provides a masked
//!     version of `byte_reverse` which is
//!     equivalent to `if_else(mask, byte_reverse(x, ...), x)`
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(byte_reverse_, byte_reverse);
}

#include <eve/module/core/impl/byte_reverse.hpp>
