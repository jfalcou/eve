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
//!   @var byte_swap_adjacent
//!   @brief swap_adjacents elementwise groups of N bytes.
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
//!      template< size_t N, eve::unsigned_value T,  integral_scalar_value N>
//!      T byte_swap_adjacent(T x, N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `n` :  size of the groups of bytes to be swapped. Must be a power of 2 and
//!              less than the half size of the elements of x
//!
//!    **Return value**
//!
//!    Return x with elementwise groups of N bytes swap_adjacentped.
//!
//!    - If N is greater to sizeof(x) 0 is returned.
//!    - If N is equal   to sizeof(x) x is returned.
//!
//!   @note Take care that eve::byte_swap_adjacent is NOT the EVE functional equivalent to std::byteswap.
//!   eve::byte_reverse IS. As the name does not say, std::byteswap reverse the order
//!   of the bytes which is not an adjacent swapping except for 16 bits words.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/byte_swap_adjacent.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::byte_swap_adjacent[mask](x, ...)` provides a masked
//!     version of `byte_swap_adjacent` which is
//!     equivalent to `if_else(mask, byte_swap_adjacent(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/byte_swap_adjacent.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(byte_swap_adjacent_, byte_swap_adjacent);
}

#include <eve/module/core/regular/impl/byte_swap_adjacent.hpp>
