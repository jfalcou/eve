//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
//!   @var is_not_infinite
//!   @brief Returns a logical true  if and only if the element is not an infinite value
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
//!      eve::as_logical<T> is_not_infinite(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real or complex argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_not_infinite(x)` is semantically  equivalent to:
//!     @code
//!     if   constexpr(floating_value<T>) return is_not_equal(abs(x), inf(as(x));
//!     else constexpr(integral_value<T>) return true_(as(x));
//!     @endcode
//!
//!     For complex entries  `is_not_infinite(z)` is semantically  equivalent to
//!     `eve::is_not_infinite(real(z)) && eve::is_not_infinite(imag(z))`,
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_not_infinite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_infinite[mask](x)` provides a masked version of
//!     `eve::is_not_infinite` which is equivalent to `if_else (mask, is_not_infinite(x),
//!     eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_not_infinite.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_not_infinite_, is_not_infinite);
}

#include <eve/module/core/regular/impl/is_not_infinite.hpp>
