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
//!   @var swap_adjacent
//!   @brief swap_adjacents  groups of N elements.
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
//!      T swap_adjacent(T x, std::integral_constant<size_t, N> n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `n` :  size of the groups of elements to be swapped. Must be a power of 2.
//!
//!    **Return value**
//!
//!    Return x with elementwise groups of N bytes swapped.
//!
//!    - If N is greater or equal to cardinal_v(x) 0 is returned.
//!    - If N is equal            to 0             x is returned.
//!
//!   @note take care that eve::swap_adjacent is NOT the functional equivalent to std::swap.
//!   eve::reverse IS. As the name does not say, std::swap reverse the order
//!   of the bytes which is not a contiguous swapping expect for 16 bits words.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/swap_adjacent.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::swap_adjacent[mask](x, ...)` provides a masked
//!     version of `swap_adjacent` which is
//!     equivalent to `if_else(mask, swap_adjacent(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/swap_adjacent.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(swap_adjacent_, swap_adjacent);
}

#include <eve/module/core/regular/impl/swap_adjacent.hpp>
