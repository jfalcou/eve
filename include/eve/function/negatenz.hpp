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
  //! @var negatenz
  //!
  //!  @brief Callable object computing the negatenz function.
  //!
  //! **Required header:** `#include <eve/function/negatenz.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the negatenz operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( value auto x, value auto y ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) product of the first parameter by the never zero sign of the second.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::negatenz
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `negatenz[cond](x, ...)` is equivalent to `if_else(cond,negatenz(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff
  //!
  //!:   **Required header:** `#include <eve/function/diff/negatenz.hpp>`
  //!
  //!    The expression `diff(negatenz)(x)` computes the derivative of the function relative to `x`.
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/negatenz.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(negatenz_, negatenz);
}

#include <eve/module/real/core/function/regular/generic/negatenz.hpp>
