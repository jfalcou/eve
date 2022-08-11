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
//!   @var is_gtz
//!   @brief Returns a logical true  if and only if the element value is greater than 0.
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
//!      eve::as_logical<T> is_gtz(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!
//!    Returns [elementwise](@ref glossary_elementwise) `x > 0`.
//!
//!  @groupheader{Example}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_gtz[mask](x)` provides a masked version of `eve::is_gtz` which is
//!     equivalent to `if_else (mask, is_gtz(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_gtz.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_gtz_, is_gtz);
}

#include <eve/module/core/regular/impl/is_gtz.hpp>
