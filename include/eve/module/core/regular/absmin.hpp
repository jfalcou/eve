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
//! @addtogroup core_arithmetic
//! @{
//!   @var absmin
//!   @brief Computes the absolute value of the minimal element
//!
//!   This is equivalent to eve::abs ( eve::min(...) ). but can be subject to optimizations.
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
//!      template< eve::value T,  eve::value... Ts>
//!      eve::common_compatible_value<T, Ts ...> absmin( T x, Ts ... xs ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`,  `...xs`: [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    The absolute value of the minimal element
//!    is returned.
//!
//!    @note
//!     If any element of the inputs is a NaN,
//!     the corresponding output element is system-dependent.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/absmin.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::absmin[mask](x, ...)` provides a masked version of `eve::absmin` which is
//!     equivalent to `eve::if_else (mask, absmin(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/absmin.cpp}
//!
//!   * eve::pedantic,  eve::numeric
//!
//!     The call `d(eve::absmin)(...)`, where d is one of these two decorators, is equivalent to
//!     `eve::abs (d( eve::min )(...))`.
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(absmin_, absmin);
}

#include <eve/module/core/regular/impl/absmin.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/absmin.hpp>
#endif
