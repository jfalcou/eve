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
  //! @addtogroup predicates
  //! @{
  //! @var is_negative
  //!
  //! @brief Callable object computing the is_negative logical value.
  //!
  //! **Required header:** `#include <eve/function/is_negative.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the is_negative logical value   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!For signed types The call `is_negative(x)` [element-wise](../../../glossary.html#value) returns true
  //!if and only if the bit of sign (most significant bit) is set.
  //!
  //!@warning
  //!   this function coincides with `is_ltz` on [integral real values](../../concepts.html#value),
  //!   but for [floating real values](../../concepts.html#value) `T`, `is_negative(mzero<`T`>)` is true and
  //!   if `n` is a Nan the result depends of the bit of sign of `n` which can be out of control although
  //!   not undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_less
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_negative[cond](x)` is equivalent to
  //! `if_else(cond,is_negative(x),false(as(is_negative(x))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/is_negative.cpp
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_negative_, is_negative);
}

#include <eve/module/real/core/function/regular/generic/is_negative.hpp>
