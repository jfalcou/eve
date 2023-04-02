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
//!   @var bit_unset
//!   @brief set to 0 the ith bit of each element.
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
//!      T bit_unset(T x, I i) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `i` :  index to unset
//!
//!    **Return value**
//!
//!    The value of the parameter is returned with the ith bit set to 0
//!    if the index is out of range the call will assert.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_unset.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_unset[mask](x, ...)` provides a masked
//!     version of `bit_unset` which is
//!     equivalent to `if_else(mask, bit_unset(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_unset.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_unset_, bit_unset);
}

#include <eve/module/core/regular/impl/bit_unset.hpp>
