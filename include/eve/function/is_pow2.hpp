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
  //! @addtogroup bits
  //! @{
  //! @var is_pow2
  //!
  //! @brief Callable object computing the is_pow2 predicate.
  //!
  //! **Required header:** `#include <eve/function/is_pow2.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the is_pow2 predicate   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( unsigned_real_value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [unsigned value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Checks [element-wise](../../../glossary.html#element-wise) if `x` is an integral power of two.
  //!
  //! ---
 //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_pow2
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_pow2[cond](x)` is equivalent to
  //! `if_else(cond,is_pow2(x),false(as(is_pow2(x))))`
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
  //! @include{lineno} doc/core/is_pow2.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_pow2_, is_pow2);
}

#include <eve/module/real/core/function/regular/generic/is_pow2.hpp>
