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
  //! @addtogroup arithmetic
  //! @{
  //! @var sqr
  //!
  //! @brief Callable object computing the sqr operation.
  //!
  //! **Required header:** `#include <eve/function/sqr.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the sqr operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes  [elementwise](@ref glossary_elementwise) the square of `x`.
  //!
  //!@warning
  //!   For  [real integral signed values](@ref eve::value)   if `saturated(abs)(x)`
  //!   is greater than [`eve::Sqrtvalmax(as(x))`](eve::sqrtvalmax) the corresponding element result is undefined .
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::sqr
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `sqr[cond](x, ...)` is equivalent to `if_else(cond,sqr(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `saturated`
  //!
  //!     **Required header:** `#include <eve/function/saturated/sqr.hpp>`
  //!
  //!     The expression `saturated(abs)(x)` computes a saturated square of `x`. Contrary to the non-decorated case, this guarantees
  //!      that the result is [elementwise](@ref glossary_elementwise) greater or equal than 0. More specifically, for any signed integer value
  //!      `x`, the expression:
  //!
  //!      `saturated(sqr)(x)`
  //!
  //!      evaluates to:
  //!
  //!      [`eve::Valmax(as(x))`](@ref eve::valmax) as soon as `saturated(abs)(x)`
  //!      is greater than [`eve::Sqrtvalmax(as(x))`](@ref eve::sqrtvalmax.html).
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/sqr.hpp>`
  //!
  //!     The expression `diff(sqr)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sqr.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqr_, sqr);
}

#include <eve/module/real/core/function/regular/generic/sqr.hpp>
