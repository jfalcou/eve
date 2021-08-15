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
  //! @var significants
  //!
  //! @brief Callable object computing the significants operation.
  //!
  //! **Required header:** `#include <eve/function/significants.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the significants operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T,integral_value U > auto operator()( T x, U n ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating value](@ref eve::value).
  //!`n`:   [integral value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes  [element-wise](@ref glossary_elementwise) the rounding to n significants digits of `x`.
  //!With null n the result is a nan.
  //!
  //!@warning
  //!   Floating numbers are not stored in decimal form. So if you try significants with
  //!   a not exactly representable number the result can be not exactly what you expect.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::significants
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `significants[cond](x, ...)` is equivalent to `if_else(cond,significants(x, ...),x)`
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
  //! @include{lineno} doc/core/significants.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(significants_, significants);
}

#include <eve/module/real/core/function/regular/generic/significants.hpp>
