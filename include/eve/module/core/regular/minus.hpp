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
//! @addtogroup core_arithmetic
//! @{
//!   @var minus
//!   @brief Computes the opposite of the parameter that must be signed.
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
//!      T minus(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     *  The result is  the opposite of `x` if this value is representable in the type of `x`.
//!
//!     *  More specifically, for signed integers the opposite value of [their lowest finite value](@ref eve::valmin)
//!        is not representable and the result is undefined behaviour.
//!
//!  @note
//!   * Although the operator notation with `-` is supported, the `-` operator on
//!     standard scalar type is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/minus.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::minus[mask](x)` provides a masked version of `eve::minus` which is
//!     equivalent to `if_else (mask, eve::minus(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/minus.cpp}
//!
//!   * eve::saturated
//!
//!     The call `eve::saturated(eve::minus)(x)` computes a saturated version of eve::minus.
//!
//!     More specifically, for any signed integer value `x`, the expression
//!     `eve::saturated(eve::minus)(eve::valmin(as(x)))` evaluates to `eve::valmax(as(x))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/minus.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(minus_, minus);
}

#include <eve/module/core/regular/impl/minus.hpp>
