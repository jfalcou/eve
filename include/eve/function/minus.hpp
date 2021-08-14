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
  //! @brief Callable object computing the minus unary operation.
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
  //!  auto operator()( value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Computes  [element-wise](@ref glossary_elementwise) a value with the same type as `x`.
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
  //!  * `saturated`
  //!
  //!     **Required header:** `#include <eve/function/saturated/minus.hpp>`
  //!
  //!     The call `saturated(minus)(x)` computes the saturated opposite of `x`. The only interest of this behaviour is that
  //!      for integral signed type T  `saturated(minus)(Valmin< T >())` returns `Valmax< T >()` and is not u.b.
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/minus.hpp>`
  //!
  //!     The expression `diff(minus)(x)` computes the derivative of the function at `x`.
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
