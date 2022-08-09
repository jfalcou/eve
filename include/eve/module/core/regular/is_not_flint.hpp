//==================================================================================================
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
//!   @var is_not_flint
//!   @brief Returns a logical true  if and only if the element value is a floating value
//!   not representing an integer
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
//!      template< eve::floating_value T >
//!      eve::as_logical<T> is_not_flint(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     The call `eve;::is_not_flint[mask](x)` is semantically  equivalent to: `eve::is_nez
//!     (eve::frac (x))`;
//!
//!     This means that x is a [floating real value](@ref eve::floating_value) not representing an
//!     integer (flint is a shorcut for 'floating integer').
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_not_flint.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_flint[mask](x)` provides a masked version of `eve::is_not_flint`
//!     which is equivalent to `if_else (mask, is_not_flint(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_not_flint.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_not_flint_, is_not_flint);
}

#include <eve/module/core/regular/impl/is_not_flint.hpp>
