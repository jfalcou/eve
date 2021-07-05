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
  //! @addtogroup arithmetic
  //! @{
  //! @var sqr
  //!
  //! @brief Callable object performing the computation of the sqr operation.
  //!
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/sqr.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
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
  //!`x`:   [value](../../concepts.html#value).
  //!
  //!
  //! **Return value**
  //!
  //!Computes  [element-wise](../../../glossary.html#elment-wise) the square of `x`.
  //!
  //!@warning
  //!   For  [real integral signed values](../../concepts.html#value)   if `saturated(abs)(x)`
  //!   is greater than [`eve::Sqrtvalmax(as(x))`](../../constants/limits/sqrtvalmax.html) the corresponding element result is undefined .
  //!
  //!
  //!
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
  //!  ====================================================================================================
  //!  * `saturated`
  //!
  //!     **Required header:**  #include <eve/function/saturated/sqr.hpp>
  //! 
  //!  
  //!     The expression `saturated(abs)(x)` computes a saturated square of `x`. Contrary to the [regular case](../decorator/regular.html), this guarantees
  //!      that the result is [`element-wise`](../../../glossary.html#element-wise) greater or equal than 0. More specifically, for any signed integer value
  //!      `x`, the expression:
  //!  
  //!      `saturated(sqr)(x)`
  //!  
  //!      evaluates to:
  //!  
  //!      [`eve::Valmax(as(x))`](../../constants/limits/valmax.html) as soon as `saturated(abs)(x)`
  //!      is greater than [`eve::Sqrtvalmax(as(x))`](../../constants/limits/sqrtvalmax.html).
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/sqr.hpp>
  //! 
  //!  
  //!     The expression `diff(sqr)(x)` computes the derivative of the function at `x`.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/sqr.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sqr_, sqr);
}

#include <eve/module/real/core/function/regular/generic/sqr.hpp>

