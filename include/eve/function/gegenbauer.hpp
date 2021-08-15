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
  //! @addtogroup polynomial
  //! @{
  //! @var gegenbauer
  //!
  //! @brief Callable object computing the gegenbauer operation.
  //!
  //! **Required header:** `#include <eve/function/gegenbauer.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the gegenbauer operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<integral_value N, floating_value T, floating_value U > auto operator()( N n, T l, U x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [integral values](../../concepts.html#value).
  //!
  //!`l`:   [floating values](../../concepts.html#value), elements must be greater than \f$-\frac12\f$.
  //!
  //!`x`:   [floating values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](../../../glossary.html#value) the value of the gegenbauer polynomial of order `n` at `l`, `x`:
  //!
  //!The result type is of the compatibility type of the  parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::gegenbauer
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `gegenbauer[cond](x, ...)` is equivalent to `if_else(cond,gegenbauer(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/gegenbauer.hpp>`
  //!
  //!     The expression `diff(gegenbauer)(n,l,x)` computes the derivative of the function relative to `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/gegenbauer.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(gegenbauer_, gegenbauer);
}

#include <eve/module/real/polynomial/function/regular/generic/gegenbauer.hpp>
