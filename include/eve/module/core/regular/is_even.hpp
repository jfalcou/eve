/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_even
//!   @brief Returns a logical true  if and only if the element value is even.
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
//!      eve::as_logical<T> is_even(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_even(x)` is semantically  equivalent to:
//!      @code
//!      if constexpr(floating_value<T>)   return eve::is_flint (x) && eve::is_flint (x/2);
//!      else constexpr(integral_value<T>) return eve::is_equal (x, (x/2)*2);
//!      @endcode
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_even.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_even[mask](x)` provides a masked version of `eve::is_even` which is
//!     equivalent to `if_else (mask, is_even(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_even.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_even_, is_even);
}

#include <eve/module/core/regular/impl/is_even.hpp>
