//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var negabsmax
//!   @brief Computes the negated absolute value of the maximal element
//!
//!   This is equivalent to -eve::abs ( eve::max )(...). but can be subject to optimizations.
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
//!      template< eve::value T,  eve::value Ts ...>
//!      eve::common_compatible_value<T, Ts ...> negabsmax( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The negated absolute value of the maximal element
//!    is returned.
//!
//!    **Note**
//!
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/negabsmax.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::negabsmax[mask](x, ...)` provides a masked version of `eve::negabsmax` which
//!     is equivalent to `eve::if_else (mask, negabsmax(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/negabsmax.cpp}
//!
//!   * eve::pedantic,  eve::numeric
//!
//!     The call `d(eve::negabsmax)(...)`, where d is one of these two decorators, is equivalent to
//!     `-eve::abs (d( eve::max )(...))`.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(negabsmax_, negabsmax);
}

#include <eve/module/core/regular/impl/negabsmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/negabsmax.hpp>
#endif
