//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/trunc.hpp>
#include <eve/module/core/regular/nearest.hpp>
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var rem
  //!
  //! @brief Callable object computing the rem operation.
  //!
  //! **Required header:** `#include <eve/function/rem.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the rem operation                                          |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //! Return the remainder after division division of `x` by `y` and is
  //! semantically equivalent to  `x-eve::trunc(``eve:div(x, y))*y`.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! The call `rem(x, y)` is equivalent to `x % y` if `x` or  `y` is an  [simd value](@ref eve::simd_value).
  //!
  //!@warning
  //!   Although the infix notation with `%` is supported, the `%` operator on
  //!   standard integral scalar type is the original one and so can lead to automatic promotion.
  //!   Moreover due to C++ limitations `%` is not available for scalar floating point values.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::rem
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `rem[cond](x, ...)` is equivalent to `if_else(cond,rem(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::toward_zero
  //!
  //!     The call `toward_zero(rem)(x, y)`  computes  `x-towardzero_(div)(x, y)*y`.
  //!      For floating point entries this call is similar to std::fmod. In particular:
  //!
  //!      * If `x` is  \f$\pm0\f$ and y is not zero,  \f$\pm0\f$ is returned.
  //!      * If `x` is \f$\pm\infty\f$, and y is not NaN, NaN is returned.
  //!      * If `y` is  \f$\pm0\f$, NaN is returned.
  //!      * If `y` is  \f$\pm\infty\f$ and `x` is finite, `x` is returned.
  //!      * If either argument is a Nan, NaN is returned.
  //!
  //!  * eve::downward
  //!
  //!     The call `downward(rem)(x, y)`  computes  `x-downward(div)(x, y)*y`.
  //!
  //!  * eve::upward
  //!
  //!     The call `upward(rem)(x, y)`  computes  `x-upward(div)(x, y)*y`.
  //!      It is not defined for unsigned values as the result can be negative.
  //!
  //!  * eve::to_nearest
  //!
  //!     The call `to_nearest(rem)(x, y)`  computes  `x-to_nearest(div)(x,y)*y`.
  //!      It is not defined for unsigned values as the result can be negative.
  //!      For floating point entries this call is similar to std::remainder.
  //!      In particular:
  //!
  //!      * If `x` is \f$\pm\infty\f$, NaN is returned
  //!      * If `y` is \f$\pm0\f$, NaN is returned
  //!      * If either argument is a Nan, NaN is returned
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/arithmetic/rem.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(rem_, rem);
}

#include <eve/module/core/regular/impl/rem.hpp>
