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
//!   @var rem
//!   @brief Computes the  remainder after division.
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
//!      template< eve::value T,  eve::value U>
//!      eve::common_compatible_t<T, U.> rem(Tx, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!       * Return the remainder after division division of `x` by `y` and is
//!         semantically equivalent to  `x- eve::trunc ( eve:div(x, y) )*y`.
//!
//!       * The call `rem(x, y)` is equivalent to `x % y` if `x` or  `y` is an  [simd value](@ref
//!       eve::simd_value).
//!
//!    **Note**
//!
//!       * Although the infix notation with `%` is supported, the `%` operator on
//!         standard integral scalar type is the original one and so can lead to automatic
//!         promotion. Moreover due to C++ limitations `%` is not available for scalar floating
//!         point values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/rem.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::rem[mask](x, ...)` provides a masked
//!     version of `rem` which is
//!     equivalent to `if_else(mask, rem(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/rem.cpp}
//!
//!   * eve::toward_zero
//!
//!       The call `toward_zero(rem)(x, y)`  computes  `x-towardzero_(div)(x, y)*y`.
//!        For floating point entries this call is similar to std::fmod. In particular:
//!
//!        * If `x` is  \f$\pm0\f$ and y is not zero,  \f$\pm0\f$ is returned.
//!        * If `x` is \f$\pm\infty\f$, and y is not NaN, NaN is returned.
//!        * If `y` is  \f$\pm0\f$, NaN is returned.
//!        * If `y` is  \f$\pm\infty\f$ and `x` is finite, `x` is returned.
//!        * If either argument is a Nan, NaN is returned.
//!
//!   * eve::downward
//!
//!       The call `downward(rem)(x, y)`  computes  `x-downward(div)(x, y)*y`.
//!
//!   * eve::upward
//!
//!       The call `upward(rem)(x, y)`  computes  `x-upward(div)(x, y)*y`.
//!        It is not defined for unsigned values as the result can be negative.
//!
//!   * eve::to_nearest
//!
//!       The call `to_nearest(rem)(x, y)`  computes  `x-to_nearest(div)(x,y)*y`.
//!        It is not defined for unsigned values as the result can be negative.
//!        For floating point entries this call is similar to std::remainder.
//!        In particular:
//!
//!        * If `x` is \f$\pm\infty\f$, NaN is returned
//!        * If `y` is \f$\pm0\f$, NaN is returned
//!        * If either argument is a Nan, NaN is returned
//!
//!        **Example**
//!
//!          @godbolt{doc/core/roundings/rem.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(rem_, rem);
}

#include <eve/module/core/regular/impl/rem.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rem.hpp>
#endif
