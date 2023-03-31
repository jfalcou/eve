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
//!   @var bit_set
//!   @brief set to 1 the ith bit of each element.
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
//!      template< eve::value T, unsigned_value I>
//!      T bit_set(T x, I0 i0) noexcept; //1
//!
//!      template< eve::value T,  auto I>
//!      T bit_set(T x, std:integral_constant<size_t, I> i) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `i` :  index to set
//!
//!    **Return value**
//!
//!    The value of the parameter is returned with the ith bit set to 1
//!        -  In the first case index out of range asserts.
//!        -  In the second case index out of range returns x unchanged.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_set.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_set[mask](x, ...)` provides a masked
//!     version of `bit_set` which is
//!     equivalent to `if_else(mask, bit_set(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_set.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_set_, bit_set);
}

#include <eve/module/core/regular/impl/bit_set.hpp>
