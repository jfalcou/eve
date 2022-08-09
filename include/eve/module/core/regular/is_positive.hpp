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
//!   @var is_positive
//!   @brief Returns a logical true  if and only if the element value is signed and
//!   has its sign bit not set
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
//!      template< eve::signed_value T >
//!      eve::as_logical<T> is_positive(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!      For signed types The call `is_positive(x)`
//!      [elementwise](@ref glossary_elementwise) returns true
//!      if and only if the bit of sign (most significant bit) is not set.
//!
//!   @note
//!     this function coincides with `is_gez` on [integral real values](@ref eve::value),
//!     but for [floating values](@ref eve::floating_value) `T`, `is_positive(mzero<`T`>)` is false
//!     and if `n` is a Nan the result depends of the bit of sign of `n` which can be out of control
//!     although not undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_positive.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_positive[mask](x)` provides a masked version of `eve::is_positive` which
//!     is equivalent to `if_else (mask, is_positive(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_positive.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_positive_, is_positive);
}

#include <eve/module/core/regular/impl/is_positive.hpp>
