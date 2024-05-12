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
//!   @var is_negative
//!   @brief Returns a logical true  if and only if the element  value is signed and
//!   has its sign bit set
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
//!      eve::as_logical<T> is_negative(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!      For signed types The call `is_negative(x)`
//!      [elementwise](@ref glossary_elementwise) returns true
//!      if and only if the bit of sign (most significant bit) is set.
//!
//!   @note
//!     this function coincides with `is_ltz` on [integral real values](@ref eve::value),
//!     but for [floating values](@ref eve::floating_value) `T`, `is_negative(mzero<`T`>)` is true
//!     and if `n` is a Nan the result depends of the bit of sign of `n` which can be out of control
//!     although not undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_negative.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_negative[mask](x)` provides a masked version of `eve::is_negative` which
//!     is equivalent to `if_else (mask, is_negative(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_negative.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_negative_, is_negative);
}

#include <eve/module/core/regular/impl/is_negative.hpp>
