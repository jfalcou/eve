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
//! @addtogroup core_predicates
//! @{
//!   @var is_not_denormal
//!   @brief Returns a logical true if and only if the element value is not denormal.
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
//!      template< eve::value T >
//!      eve::as_logical<T> is_not_denormal(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_not_denormal(x)` is semantically  equivalent to:
//!     `(eve::abs(x) >=  eve::smallestposval(eve::as(x))) || eve::is_eqz(x)`,
//!     in particular this is always true for integral types.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_not_denormal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_denormal[mask](x)` provides a masked version
//!     of `eve::is_not_denormal` which is
//!     equivalent to `if_else (mask, is_not_denormal(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_denormal.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_not_denormal_, is_not_denormal);
}

#include <eve/module/core/regular/impl/is_not_denormal.hpp>
