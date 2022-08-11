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
//!   @var is_gez
//!   @brief Returns a logical true  if and only if the element value is greater or equal to 0.
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
//!      eve::as_logical<T> is_gez(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) `x >= 0`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_gez.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_gez[mask](x)` provides a masked version of `eve::is_gez` which is
//!     equivalent to `if_else (mask, is_gez(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_gez.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_gez_, is_gez);
}

#include <eve/module/core/regular/impl/is_gez.hpp>
