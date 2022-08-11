//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
//!   @var bit_or
//!   @brief Computes the bitwise OR of its arguments.
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
//!      T bit_or(T x, Ts... xs) noexcept;
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
//!      The value of the bitwise OR of its arguments in the type of the first one
//!      is returned.
//!
//!    @note
//!      Although the infix notation with `|` is supported for two parameters, the `|` operator on
//!      standard scalar types is the original one and so can lead to automatic promotion.
//!      Moreover, and due to C++ limitations is not available for floating point scalar entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_or.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_or[mask](x, ...)` provides a masked
//!     version of `bit_or` which is
//!     equivalent to `if_else(mask, bit_or(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_or.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_or_, bit_or);
}

#include <eve/module/core/regular/impl/bit_or.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_or.hpp>
#endif
