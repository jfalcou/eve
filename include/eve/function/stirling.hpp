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
  //! @addtogroup special
  //! @{
  //! @var stirling
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/stirling.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the stirling operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the stirling operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, floating_value U > auto operator()( Tx ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](../../concepts.html#value).
  //!
  //!`x`:   [floating value](../../concepts.html#value).
  //!
  //!
  //! **Return value**
  //!
  //!Returns [element-wise](../../../glossary.html#value) \sqrt{2 \pi} x^{x-\frac12} e^{-x} ( 1 + \frac1{x} P(\frac1{x}))$
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::stirling
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `stirling[cond](x, ...)` is equivalent to `if_else(cond,stirling(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  decorators NOT FOUND
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/stirling.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(stirling_, stirling);
}

#include <eve/module/real/special/function/regular/generic/stirling.hpp>

