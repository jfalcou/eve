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
//!   @var bit_andnot
//!   @brief Computes the bitwise ANDNOT of its arguments.
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
//!      T bit_andnot(T x, Ts... xs) noexcept;
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
//!     * For two parameters it computes the  bitwise ANDNOT of the two parameters
//!     * For more than two parameters the call is  semantically equivalent to to `bit_andnot(a0,
//!     bit_and(xs...))`
//!     *  The value returned is in the type of the first parameter
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_andnot.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_andnot[mask](x, ...)` provides a masked
//!     version of `bit_andnot` which is
//!     equivalent to `if_else(mask, bit_andnot(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/bit_andnot.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_andnot_, bit_andnot);
}

#include <eve/module/core/regular/impl/bit_andnot.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_andnot.hpp>
#endif
