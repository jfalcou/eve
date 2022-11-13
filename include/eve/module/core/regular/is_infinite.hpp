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
//!   @var is_infinite
//!   @brief Returns a logical true  if and only if the element is an infinite value
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
//!      eve::as_logical<T> is_infinite(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real or complex argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     For real entries the call `is_infinite(x)` is semantically  equivalent to
//!     `eve::is_equal(eve::abs(x), eve::inf(as(x))`,
//!     in particular this is always false for integral types.
//!
//!     For complex entries  `is_infinite(z)` is semantically  equivalent to
//!     `eve::is_infinite(real(z)) || eve::is_infinite(imag(z))`,
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_infinite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_infinite[mask](x)` provides a masked
//!     version of `eve::is_infinite` which
//!     is equivalent to `if_else (mask, is_infinite(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_infinite.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_infinite_, is_infinite);
}

#include <eve/module/core/regular/impl/is_infinite.hpp>
