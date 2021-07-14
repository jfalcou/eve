//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

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
  //! | `operator()` | the rem operation   |
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
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Return the remainderafter division division of `x` by `y`.
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the two parameters.
  //!
  //! The call `rem(x, y)` is equivalent to `x % y` if `x` or  `y` is an  [simd value](../../concepts.html#value).
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
  //!  ====================================================================================================
  //!  * `toward_zero`
  //!     The call `toward_zero(rem)(x, y)`  computes  `x-towardzero_(div)(x, y)*y`.
  //!      For floating point entries this call is similar to std::fmod. In particular:
  //!  
  //!      * If `x` is  \f$\pm0\f$ and y is not zero,  \f$\pm0\f$ is returned.
  //!      * If `x` is \f$\pm\infty\f$, and y is not NaN, NaN is returned.
  //!      * If `y` is  \f$\pm0\f$, NaN is returned.
  //!      * If `y` is  \f$\pm\infty\f$ and `x` is finite, `x` is returned.
  //!      * If either argument is a Nan, NaN is returned.
  //!  
  //!  * `downward`
  //!     The call `downward(rem)(x, y)`  computes  `x-downward(div)(x, y)*y`.
  //!  
  //!  * `upward`
  //!     The call `upward(rem)(x, y)`  computes  `x-upward(div)(x, y)*y`.
  //!      It is not defined for unsigned values as the result can be negative.
  //!  
  //!  * `to_nearest`
  //!     The call `to_nearest(rem)(x, y)`  computes  `x-to_nearest(div)(x,y)*y`.
  //!      It is not defined for unsigned values as the result can be negative.
  //!      For floating point entries this call is similar to std::remainder.
  //!      In particular:
  //!  
  //!      * If `x` is \f$\pm\infty\f$, NaN is returned
  //!      * If `y` is \f$\pm0\f$, NaN is returned
  //!      * If either argument is a Nan, NaN is returned
  //!  
  //!  Masked calls
  //!  ====================================================================================================
  //!   The [masked](../../../tutorial/masking.html) calls `rem[cond](x,y)` and `d_(rem[cond])(x,y)` where d_ is one
  //!   of the supported decorators and `cond` satisfies the
  //!   [conditionnal-expression](../../concepts.html#conditionnal) requirements are supported.
  //!  
  //!   More precisely, if `cond` is a mere [logical value](../../concepts.html#value) these expressions compute
  //!   the remainder (resp the decorated remainder) of `x` and `y`
  //!   if the condition `cond` is satisfied else returns  `x`. The calls are respectively equivalent to :
  //!  
  //!   *  `if_else(cond, rem(x,y), x)`,
  //!   *  `if_else(cond, d_(rem)(x,y), x)`;
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/rem.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(rem_, rem);
}

#include <eve/module/real/core/function/regular/generic/rem.hpp>
