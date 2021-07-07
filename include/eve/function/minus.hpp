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
  //! @var minus
  //!
  //! @brief Callable object performing the computation of the minus unary operation.
  //!
  //! **Required header:** `#include <eve/function/minus.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the minus unary operation   |
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
  //!Computes  [element-wise](../../../glossary.html#elment-wise) a value with the same type as `x`.
  //!The result is  the opposite of `x` if this value is representable in the type of `x`.
  //!More specifically, for signed integers the opposite value of [their lowest finite value](../../constants.html#valmin)
  //!is not representable and the result is undefined behaviour.
  //!
  //!@warning
  //!   Although the operator notation with `-` is supported, the `-` operator on
  //!   standard scalar type is the original one and so can lead to automatic promotion.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::minus
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `minus[cond](x, ...)` is equivalent to `if_else(cond,minus(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `saturated`
  //!
  //!     **Required header:**  #include <eve/function/saturated/minus.hpp>
  //! 
  //!  
  //!     The call `saturated(minus)(x)` computes the saturated opposite of `x`. The only interest of this behaviour is that
  //!      for integral signed type T  `saturated(minus)(Valmin< T >())` returns `Valmax< T >()` and is not u.b.
  //!  
  //!  * `diff`
  //!
  //!     **Required header:**  #include <eve/function/diff/minus.hpp>
  //! 
  //!  
  //!     The expression `diff(minus)(x)` computes the derivative of the function at `x`.
  //!  
  //!  Masked calls
  //!  ====================================================================================================
  //!   The [masked](../../../tutorial/masking.html) calls `minus[cond](x)` and `saturated(minus[cond])(x)` where `cond` satisfies the
  //!   [conditionnal-expression](../../concepts.html#conditionnal) requirements are supported.
  //!  
  //!   More precisely, if `cond` is
  //!   a mere [logical value](../../concepts.html#value) these expressions compute the opposite (resp the saturated  opposite) of `x`
  //!   if the condition `cond` is satisfied else returns  `x`. The calls are respectively equivalent to :
  //!  .
  //!   *  `if_else(cond, minus(x), x)`,
  //!   *  `if_else(cond, saturated(minus)(x), x)`;
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/minus.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(minus_, minus);
}

#include <eve/module/real/core/function/regular/generic/minus.hpp>
