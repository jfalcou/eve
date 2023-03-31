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
//!   @var bit_swap_adjacent
//!   @brief swap_adjacents elementwise groups of N bits.
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
//!      T bit_swap_adjacent(T x, std::integral_constant<size_t, N> n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `n` :  size of the groups of bits to be swap_adjacentped. n MUST be a power of 2
//!              else the call will assert.
//!
//!    **Return value**
//!
//!    Return x with pairs of contiguous groups of N bits swapped in each element.
//!
//!    - If N is greater or equal to sizeof(x)*8 0 is returned.
//!    - If N is equal            to 0           x is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_swap_adjacent.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_swap_adjacent[mask](x, ...)` provides a masked
//!     version of `bit_swap_adjacent` which is
//!     equivalent to `if_else(mask, bit_swap_adjacent(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_swap_adjacent.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_swap_adjacent_, bit_swap_adjacent);
}

#include <eve/module/core/regular/impl/bit_swap_adjacent.hpp>
