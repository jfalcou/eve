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
//!   @var bit_not
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
//!      template< eve::value T >
//!      T bit_not(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the bitwise NOT of the parameter is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_not.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_not[mask](x, ...)` provides a masked
//!     version of `bit_not` which is
//!     equivalent to `if_else(mask, bit_not(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_not.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_not_, bit_not);
}

#include <eve/module/core/regular/impl/bit_not.hpp>
