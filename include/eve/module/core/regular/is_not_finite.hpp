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
//!   @var is_not_finite
//!   @brief Returns a logical true  if and only if the element is not a finite value
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
//!      eve::as_logical<T> is_not_finite(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real or complex argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     For real entries the call `is_not_finite(x)` is semantically  equivalent to:
//!     @code
//!     if   constexpr(floating_value<T>) return is_nan(x-x);
//!     else constexpr(integral_value<T>) return false_(as(x));
//!     @endcode
//!
//!     For complex entries  `is_infinite(z)` is semantically  equivalent to
//!     `eve::is_not_finite(real(z)) || eve::is_not_finite(imag(z))`,
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_not_finite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_finite[mask](x)` provides a masked version of `eve::is_not_finite`
//!     which is equivalent to `if_else (mask, is_not_finite(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_not_finite.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_not_finite_, is_not_finite);
}

#include <eve/module/core/regular/impl/is_not_finite.hpp>
