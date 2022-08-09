/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_pow2
//!   @brief Returns a logical true  if and only if the element value is a power of 2.
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
//!      eve::as_logical<T> is_pow2(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Checks [elementwise](@ref glossary_elementwise) if `x` is an integral power of two.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_pow2.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_pow2[mask](x)` provides a masked version of `eve::is_pow2` which is
//!     equivalent to `if_else (mask, is_pow2(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_pow2.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_pow2_, is_pow2);
}

#include <eve/module/core/regular/impl/is_pow2.hpp>
