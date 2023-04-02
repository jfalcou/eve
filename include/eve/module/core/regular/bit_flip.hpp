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
//!   @var bit_flip
//!   @brief flip the value the ith bit of each element.
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
//!      template< eve::value T, integral_value I>
//!      T bit_flip(T x, I i) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `i` :  index to flip.
//!
//!    **Return value**
//!
//!    The value of the parameter is returned with the ith bit flip.
//!    if the index is out of range the call will assert.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_flip.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_flip[mask](x, ...)` provides a masked
//!     version of `bit_flip` which is
//!     equivalent to `if_else(mask, bit_flip(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_flip.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_flip_, bit_flip);
}

#include <eve/module/core/regular/impl/bit_flip.hpp>
