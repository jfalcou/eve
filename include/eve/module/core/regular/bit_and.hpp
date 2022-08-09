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
//!   @var bit_and
//!   @brief Computes the bitwise AND of its arguments.
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
//!      T bit_and(T x, Ts... xs) noexcept;
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
//!      The value of the bitwise AND of its arguments in the type of the first one
//!      is returned.
//!
//!    @note
//!
//!      Although the infix notation with `&` is supported for two parameters, the `&` operator on
//!      standard scalar types is the original one and so can lead to automatic promotion.
//!      Moreover, and due to C++ limitations is not available for floating point scalar entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_and.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_and[mask](x, ...)` provides a masked
//!     version of `bit_and` which is
//!     equivalent to `if_else(mask, bit_and(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_and.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_and_, bit_and);
}

#include <eve/module/core/regular/impl/bit_and.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_and.hpp>
#endif
