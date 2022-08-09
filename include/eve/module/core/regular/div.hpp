//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var div
//!   @brief Computes the  division of multiple values.
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
//!      template< eve::value Ts ... >
//!      eve::common_compatible_t<T, Ts ...> div(Ts ... xs) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `...xs` :  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      If the arguments are \f$(x_i)_{0\le i\le n}\f$ The value of \f$x/\prod_1^n x_i\f$
//!      is returned.
//!
//!    @note
//!
//!      * With two parameters, the call `div(x, y)` is equivalent to `x / y`
//!        if `x` or  `y` is an  [simd value](@ref eve::simd_value).
//!
//!      * Although the infix notation with `/` is supported for
//!        two parameters, the `/` operator on
//!        standard scalar types is the original one and so can lead to automatic promotion.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/div.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::div[mask](x, ...)` provides a masked
//!     version of `div` which is
//!     equivalent to `if_else(mask, div(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/div.cpp}
//!
//!   * eve::saturated
//!
//!       The expression `eve::saturated(eve::div)(x, xs...)` computes the saturated
//!       division of `x` by  all `xs`. The result is semantically equivalent to
//!       `saturated(div)(x, saturated(mul)(xs...))` but is always defined even if
//!       the denominator is 0.
//!
//!       The relevant cases are just in fact  the division by 0 for integral types
//!       in which case the result is [`eve::valmin(as(x))`](@ref eve::valmin) or
//!       [`eve::valmax(as(x))`](ref eve::valmax) according to the dividend sign, and
//!       the division of [`eve::valmin(as(x))`](@ref eve::valmin)
//!       by -1 that produces [`eve::valmax(as(x))`](@ref eve::valmax).
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/div.cpp}
//!
//!   * eve::toward_zero, eve::downward, eve::upward, eve::to_nearest
//!
//!       The calls `d(div)(x, y)` where d is one of these 4 decorators produce respectively
//!
//!           * `eve::trunc (div(x, y))` for eve::toward_zero.
//!           * `eve::floor (div(x, y))` for deve::downward.
//!           * `eve::ceil (div(x, y))`  for eve::upward.
//!           * `eve::nearest (div(x,y))`for eve::to_nearest.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/roundings/div.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(div_, div);
}

#include <eve/module/core/regular/impl/div.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/div.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/div.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/div.hpp>
#endif
