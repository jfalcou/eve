/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_less_equal
//!   @brief Returns a logical true  if and only if the element value of the first parameter is
//!          less or equal to the second one.
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
//!      template< eve::value T, eve::value U >
//!      eve::as_logical<T> is_less_equal(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_less_equal(x,y)`  is semantically  equivalent to `!(x <= y)`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_less_equal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_less_equal[mask](x,y)` provides a masked version of `eve::is_less_equal`
//!     which is equivalent to `if_else (mask, is_less_equal(x), eve::false( eve::as(x,y)))`.
//!
//!     **Example**
//!
//!     @godbolt{doc/core/masked/is_less_equal.cpp}
//!
//!   * `definitely`
//!
//!     The expression `definitely(is_not_less_equal)(x, y, t)` where `x` and `y` must be
//!     floating point values, evaluates to true if and only if and only if `x` is definitely not less
//!     or equal to `y`. This means that the pair `x, y` is unordered or:
//!
//!       * if `t` is a floating_value then  \f$(x \ge y + t \max(|x|, |y|))\f$
//!       * if `t` is a positive integral_value then \f$(x \ge \mbox{next}(y, t)\f$;
//!       * if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
//!
//!     **Example**
//!
//!     @godbolt{doc/core/fuzzy/is_less_equal.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(is_not_less_equal_, is_not_less_equal);
}

#include <eve/module/core/regular/impl/is_not_less_equal.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_not_less.hpp>
#endif
