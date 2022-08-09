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
//!   @var is_ltz
//!   @brief Returns a logical true  if and only if the element value is less than 0.
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
//!      eve::as_logical<T> is_ltz(T x) noexcept;
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
//!    Returns [elementwise](@ref glossary_elementwise) `x < 0`.
//!
//!  @groupheader{Example}
//!
//!     @godbolt{doc/core/regular/is_ltz.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_ltz[mask](x)` provides a masked version of `eve::is_ltz` which is
//!     equivalent to `if_else (mask, is_ltz(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_ltz.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_ltz_, is_ltz);
}

#include <eve/module/core/regular/impl/is_ltz.hpp>
#include <eve/module/core/regular/impl/simd/x86/is_ltz.hpp>
