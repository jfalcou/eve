//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
//!   @var firstbitunset
//!   @brief Computes [elementwise](@ref glossary_elementwise) the bit pattern
//!   in which the only bit set (if it exists) is the first bit unset in the input.
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
//!      template< eve::unsigned_value T >
//!      T firstbitunset(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!       Computes [elementwise](@ref glossary_elementwise) the bit pattern in
//!       which the only bit set (if it exists) is
//!       the first bit unset (beginning with the least significant bit) in the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/firstbitunset.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::firstbitunset[mask](x)` provides a masked
//!     version of `firstbitunset` which is
//!     equivalent to `if_else(mask, firstbitunset(x), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/firstbitunset.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(firstbitunset_, firstbitunset);
}

#include <eve/module/core/regular/impl/firstbitunset.hpp>
