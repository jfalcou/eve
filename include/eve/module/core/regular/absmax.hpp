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
//!   @var absmax
//!   @brief Computes the absolute value of the maximal element
//!
//!   This is equivalent to eve::abs ( eve::max )(...). but can be subject to optimizations.
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
//!      eve::common_compatible_value<T, Ts ...> absmax( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The absolute value of the maximal element
//!    is returned.
//!
//!    **Note**
//!
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/absmax.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::absmax[mask](x, ...)` provides a masked version of `eve::absmax` which is
//!     equivalent to `eve::if_else (mask, absmax(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/absmax.cpp}
//!
//!   * eve::pedantic,  eve::numeric
//!
//!     The call `d(eve::absmax)(...)`, where d is one of these two decorators, is equivalent to
//!     `eve::abs (d( eve::max )(...))`.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(absmax_, absmax);
}

#include <eve/module/core/regular/impl/absmax.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmax.hpp>
#endif
