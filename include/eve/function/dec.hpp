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
  //! @var dec
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/dec.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the dec unary operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the dec unary operation   |
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
  //!Computes  [element-wise](../../../glossary.html#elment-wise) a value with the same type as `x`.
  //!The result is `x-1`.
  //!
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::dec
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `dec[cond](x, ...)` is equivalent to `if_else(cond,dec(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `saturated`
  //!
  //!     **Required header: 
  //! 
  //!       #include <eve/function/saturated/dec.hpp>`
  //! 
  //!  
  //!     The call `saturated(dec)(x)` computes the saturated opposite of `x`. The only interest of this behaviour is that
  //!      for integral type T  `saturated(dec)(Valmin< T >())` returns `Valmin< T >()`.
  //!  
  //!  * `diff`
  //!
  //!     **Required header: 
  //! 
  //!       #include <eve/function/diff/dec.hpp>`
  //! 
  //!  
  //!     The expression `diff(dec)(x)` computes the derivative of the function at `x`.
  //!  
  //!  Masked calls
  //!  ====================================================================================================
  //!   The [masked](../../../tutorial/masking.html) calls `dec[cond](x)` and `saturated(dec[cond])(x)` where `cond` satisfies the
  //!   [conditionnal-expression](../../concepts.html#conditionnal) requirements are supported.
  //!  
  //!   More precisely, if `cond` is
  //!   a mere [logical value](../../concepts.html#value) these expressions compute the decrement (resp the saturated  decrement) of `x`
  //!   if the condition `cond` is satisfied else returns  `x`. The calls are respectively equivalent to :
  //!  
  //!   *  `if_else(cond, dec(x), x)`,
  //!   *  `if_else(cond, saturated(dec)(x), x)`;
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/dec.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(dec_, dec);
}

#include <eve/module/real/core/function/regular/generic/dec.hpp>

