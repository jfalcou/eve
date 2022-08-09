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
//!   @var is_unordered
//!   @brief Returns a logical true  if and only if at least one of the parameters is NaN.
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
//!      eve::as_logical<T> is_unordered(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_unordered(x,y)`  is semantically  equivalent
//!    to `eve::is_nan(x) || eve::is_nan(y)`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_unordered.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_unordered[mask](x,y)` provides a masked version of `eve::is_unordered`
//!     which is equivalent to `if_else (mask, is_unordered(x), eve::false( eve::as(x,y)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_unordered.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_unordered_, is_unordered);
}

#include <eve/module/core/regular/impl/is_unordered.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_unordered.hpp>
#endif
