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
//!   @var bit_swap
//!   @brief computes the ones complement of the parameter.
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
//!      template< auto N, eve::integral_value T >
//!      T bit_swap(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!
//!  **Template parameters**
//!
//!     * N: size of the groups of bits to be swapped
//!
//!    **Return value**
//!
//!    Return x with elementwise groups of N bits swapped.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_swap.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_swap[mask](x, ...)` provides a masked
//!     version of `bit_swap` which is
//!     equivalent to `if_else(mask, bit_swap(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_swap.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_swap_, bit_swap);
}

#include <eve/module/core/regular/impl/bit_swap.hpp>
