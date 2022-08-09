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
//!   @var is_odd
//!   @brief Returns a logical true  if and only if the element value is odd.
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
//!      eve::as_logical<T> is_odd(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_odd(x)` is semantically  equivalent to:
//!      @code
//!      if constexpr(floating_value<T>)   return (x != dec(x)) && eve::is_even(dec(x));
//!      else constexpr(integral_value<T>) return eve::is_nez (x & one(as(x));
//!      @endcode
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_odd.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_odd[mask](x)` provides a masked version of `eve::is_odd` which is
//!     equivalent to `if_else (mask, is_odd(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_odd.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_odd_, is_odd);
}

#include <eve/module/core/regular/impl/is_odd.hpp>
