//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct rem_t : elementwise_callable<rem_t, Options, upward_option, downward_option,
                                      to_nearest_option, toward_zero_option>
  {
    template<eve::value T0, value T1>
    requires(eve::same_lanes_or_scalar<T0, T1>)
    EVE_FORCEINLINE constexpr common_value_t<T0, T1> operator()(T0 t0, T1 t1) const noexcept
    {
      return EVE_DISPATCH_CALL(t0, t1);
    }

    EVE_CALLABLE_OBJECT(rem_t, rem_);
  };

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
//!      eve::common_value_t<T, U> rem(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:   [real](@ref eve::value) argumentx.
//!
//!   **Return value**
//!
//!      Return the remainder after division division of `x` by `y` and is
//!      semantically equivalent to  `x- eve::trunc ( eve:div(x, y) )*y`.
//!
//!      The call `rem(x, y)` is equivalent to `x % y` if `x` or  `y` is an
//!      [simd value](@ref eve::simd_value).
//!
//!    @note
//!       * Although the infix notation with `%` is supported, the `%` operator on
//!         standard integral scalar type is the original one and so can lead to automatic
//!         promotion. Moreover due to C++ limitations `%` is not available for scalar floating
//!         point values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/rem.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::rem[mask](x, ...)` provides a masked
//!     version of `rem` which is
//!     equivalent to `if_else(mask, rem(x, ...), x)`
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
//! @}
//================================================================================================
  inline constexpr auto rem = functor<rem_t>;
}

#include <eve/module/core/regular/impl/rem.hpp>

// #if defined(EVE_INCLUDE_ARM_HEADER)
// #  include <eve/module/core/regular/impl/simd/arm/neon/rem.hpp>
// #endif
