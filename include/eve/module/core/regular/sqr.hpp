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
//! @addtogroup core_arithmetic
//! @{
//!   @var sqr
//!   @brief Computes the square of the parameter.
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
//!      T sqr(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    value containing the [elementwise](@ref glossary_elementwise)
//!    square of `x` if it is representable in this type.
//!
//!  @note
//!      For  [integral signed values](@ref eve::value)   if `eve::saturated(eve::abs)(x)`
//!      is greater than `eve::Sqrtvalmax(as(x))` the corresponding element result
//!      is undefined.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/sqr.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::sqr[mask](x)` provides a masked version of `eve::sqr` which is
//!     equivalent to `if_else (mask, sqr(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/sqr.cpp}
//!
//!   * eve::saturated
//!
//!     The call `eve::saturated(eve::sqr)(x)` computes a saturated version of eve::sqr.
//!
//!     Contrary to the  non-decorated case, it guarantees
//!      that the result is [elementwise](@ref glossary_elementwise) greater or equal than 0. More
//!      specifically, for any signed integer value `x`, the expression:
//!
//!      `saturated(sqr)(x)`
//!
//!      evaluates to:
//!
//!      [`eve::valmax(as(x))`](@ref eve::valmax) as soon as `eve::saturated(eve::abs)(x)`
//!      is greater than `eve::sqrtvalmax(as(x))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/sqr.cpp}
//!
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(sqr_, sqr);
}

#include <eve/module/core/regular/impl/sqr.hpp>
