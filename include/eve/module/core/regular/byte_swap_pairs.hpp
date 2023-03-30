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
//!   @brief swap chosen pairs of bytes in each vector element.
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
//!      template<unsigned_value T, auto I0, auto I1 >
//!      T byte_swap_pairs(T x
//!                      , std::integral_constant<size_t, I0> const & i0>
//!                      , std::integral_constant<size_t, I1> const & i1);
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
//!    Return x byte i0 and i1 swapped in each element of x.
//!    Assert if i0 or i1 are out of range.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/byte_swap_pairs.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::byte_swap_pairs[mask](x, ...)` provides a masked
//!     version of `byte_swap_pairs` which is
//!     equivalent to `if_else(mask, byte_swap_pairs(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/byte_swap_pairs.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(byte_swap_pairs_, byte_swap_pairs);
}

#include <eve/module/core/regular/impl/byte_swap_pairs.hpp>
