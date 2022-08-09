//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_ornot
//!   @brief Computes the bitwise ORNOT of its arguments.
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
//!      template< eve::value T, eve::value Ts... >
//!      T bit_ornot(T x, Ts... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:       first [argument](@ref eve::value).
//!     * `xs...` :  other [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!     * For two parameters it computes the  bitwise ORNOT of the two parameters
//!     * For more than two parameters the call is  semantically equivalent to to `bit_ornot(a0,
//!     bit_or(xs...))`
//!     *  The value returned is in the type of the first parameter
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_ornot.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_ornot[mask](x, ...)` provides a masked
//!     version of `bit_ornot` which is
//!     equivalent to `if_else(mask, bit_ornot(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_ornot.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_ornot_, bit_ornot);
}

#include <eve/module/core/regular/impl/bit_ornot.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_ornot.hpp>
#endif
