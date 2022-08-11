//==================================================================================================
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
//!   @var is_not_imag
//!   @brief Returns a logical true  if and only if the element value is not imaginary.
//!
//!   For real entries 0 is the only imaginary number: its real part is 0!
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
//!      eve::as_logical<T> is_not_imag(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) `x != 0` for real entries.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_not_imag.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_imag[mask](x)` provides a masked version of `eve::is_not_imag` which
//!     is equivalent to `if_else (mask, is_not_imag(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_not_imag.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_not_imag_, is_not_imag);
}

#include <eve/module/core/regular/impl/is_not_imag.hpp>
