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
//! @addtogroup core_predicates
//! @{
//!   @var is_lessgreater
//!   @brief Returns a logical true  if and only if the elements pair are not equal or unordered.
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
//!      template< eve::value T, eve::value U >
//!      eve::as_logical<T> is_lessgreater(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [arguments](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_lessgreater(x, y)`  is semantically  equivalent to `x < y || x > y`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_lessgreater.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_lessgreater[mask](x, y)` provides a masked version of
//!     `eve::is_lessgreater` which is equivalent to `if_else (mask, is_lessgreater(x, y),
//!     eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_lessgreater.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_lessgreater_, is_lessgreater);
}

#include <eve/module/core/regular/impl/is_lessgreater.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_lessgreater.hpp>
#endif
