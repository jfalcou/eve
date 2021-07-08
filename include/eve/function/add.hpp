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
  //! @var add
  //!
  //! @brief Callable object performing the sum of multiple values.
  //!
  //! **Required header:** `#include <eve/function/add.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the absolute value of its parameter               |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::value auto const&... xs) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `xs`:  Instances of eve::value
  //!
  //! **Return value**
  //!
  //! A value of the [common compatible type](@ref common_compatible) of all `xs` containing the
  //! [elementwise](@ref glossary_elementwise) sum of all `xs`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::add
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `add[cond](x0,xs...)` is equivalent
  //!  to `if_else(cond,add(x0,xs...),x0)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::saturated
  //!
  //!     **Required header:** `#include <eve/function/saturated/abs.hpp>`
  //!
  //!     The expression `eve::saturated(eve::add)(xs...)` computes the saturated sum of all `xs`.
  //!
  //!   * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/add.hpp>`
  //!
  //!     The expression `eve::diff<N>(eve::add)(xs...)` computes the derivative of the sum
  //!     of `xs...` over the Nth parameters.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/h6YKzz5jc)
  //!
  //! @include{lineno} doc/core/add.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(add_, add);
}

#include <eve/module/real/core/function/regular/generic/add.hpp>
