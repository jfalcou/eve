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
//!   @var is_normal
//!   @brief Returns a logical true if and only if the element value is normal.
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
//!      eve::as_logical<T> is_normal(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_normal(x)` is semantically  equivalent to:
//!
//!     @code
//!       if   constexpr(floating_value<T>) return (eve::abs(x) >= eve::smallestposval(as(x)));
//!       else constexpr(integral_value<T>) return eve::false_(as(x));
//!    @endcode
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_normal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::is_normal[mask](x)` provides a masked version of `eve::is_normal` which is
//!     equivalent to `if_else (mask, is_normal(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_normal.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_normal_, is_normal);
}

#include <eve/module/core/regular/impl/is_normal.hpp>
