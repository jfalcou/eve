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
//!   @var is_finite
//!   @brief Returns a logical true  if and only if the element is a finite value
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
//!      eve::as_logical<T> is_finite(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real or complex argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     For real entries he call `is_finite(x)` is semantically  equivalent to `eve::is_not_nan(x-x)`, in particular
//!     this is always true for integral types.
//!
//!     For complex entries  `is_infinite(z)` is semantically  equivalent to
//!     `eve::is_finite(real(z)) && eve::is_finite(imag(z))`,
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_finite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_finite[mask](x)` provides a masked version of `eve::is_finite` which is
//!     equivalent to `if_else (mask, is_finite(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_finite.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_finite_, is_finite);
}

#include <eve/module/core/regular/impl/is_finite.hpp>
