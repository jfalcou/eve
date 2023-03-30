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
//!   @var bit_swap_pairs
//!   @brief swap_pairs elementwise groups of N bits.
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
//!      template<eve::unsigned_value T, unsigned_value I0, unsigned_value I1 >
//!      T bit_swap_pairs(T x, I0 i0, I1 i1);
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `i0` : first index
//!     * `i1` : second index
//!
//!    **Return value**
//!
//!    Return x with elementwise bit i0 and i1 swapped.
//!    Assert if i0 or i1 are out of range.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_swap_pairs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_swap_pairs[mask](x, ...)` provides a masked
//!     version of `bit_swap_pairs` which is
//!     equivalent to `if_else(mask, bit_swap_pairs(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_swap_pairs.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_swap_pairs_, bit_swap_pairs);
}

#include <eve/module/core/regular/impl/bit_swap_pairs.hpp>
