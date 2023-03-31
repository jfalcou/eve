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
//!      template< size_t N, eve::integral_value T >
//!      T byte_swap_adjacent(T x, std::integral_constant<size_t, N> n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `n` :  size of the groups of bytes to be swap_adjacentped. Must be a power of 2.
//!
//!    **Return value**
//!
//!    Return x with elementwise groups of N bytes swap_adjacentped.
//!
//!    - If N is greater to sizeof(x) 0 is returned.
//!    - If N is equal   to sizeof(x) x is returned.
//!
//!   @note take care that eve::byte_swap_adjacent is NOT the functional equivalent to std::byte_swap_adjacent.
//!   eve::byte_reverse IS. As the name does not say, std::byte_swap_adjacent reverse the order
//!   of the bytes which is not a contiguous swap_adjacentping expect for 16 bits words.
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
