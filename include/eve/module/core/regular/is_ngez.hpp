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
//!   @var is_ngez
//!   @brief Returns a logical true  if and only if the element value is not greater or equal to 0.
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
//!      eve::as_logical<T> is_ngez(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) `!(x >= 0)`.
//!
//!   @note
//!
//!    This is not equivalent to `(x <  0)` for floating values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_ngez.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_ngez[mask](x)` provides a masked version of `eve::is_ngez` which is
//!     equivalent to `if_else (mask, is_ngez(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_ngez.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_ngez_, is_ngez);
}

#include <eve/module/core/regular/impl/is_ngez.hpp>
