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
  //! @addtogroup rounding
  //! @{
  //! @var round
  //!
  //! @brief Callable object computing the round operation.
  //!
  //! **Required header:** `#include <eve/function/round.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the round operation   |
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
  //! **Return value**
  //!
  //!Computes  [element-wise](../../../glossary.html#elment-wise) the integer nearest to `x`.
  //!
  //!If `x` is an exact half-integer the rouding is made to the nearest even integer.
  //!
  //!The call to `round(a)` is equivalent to the call `nearest(a)`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::round
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `round[cond](x, ...)` is equivalent to `if_else(cond,round(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `downward`
  //!     The expression `downward(round)(x)` is equivalent to `floor(x)`.
  //!  
  //!  * `upward`
  //!     The expression `upward(round)(x)` is equivalent to `ceil(x)`.
  //!  
  //!  * `to_nearest`
  //!     The expression `to_nearest(round)(x)` is equivalent to `nearest(x)`.
  //!  
  //!  * `toward_zero`
  //!     The expression `toward_zero(round)(x)` is equivalent to `trunc(x)`.
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/round.hpp>
  //!  
  //!     The expression `diff(round)(x)` computes the derivative of the function at `x` (it is the same as `nearest`).
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/round.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(round_, round);
}

#include <eve/module/real/core/function/regular/generic/round.hpp>
