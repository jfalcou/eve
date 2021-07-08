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
  //! @addtogroup combinatorial
  //! @{
  //! @var fibonacci
  //!
  //! @brief Callable object performing the computation of the nth value of the fibonacci sequence.
  //!
  //! **Required header:** `#include <eve/function/fibonacci.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the nth value of the fibonacci sequence  |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value U, unsigned_value N > auto operator()( T x, U y, N n ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [floating values](../../concepts.html#value).
  //!
  //!`n`:   [unsigned value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //! The result type is the [compatibility result](../../concept.html#compatibility) of the two first parameters,
  //! vectorized with the cardinality of the third one if necessary.
  //!
  //! The recurrence formula defining the fibonacci sequence is:
  //!
  //!      - r(0) = x
  //!      - r(1) = y
  //!      - r(i+2) = r(i+1)+r(i),  i > 2
  //!
  //! The function return elementwise r(n), but the result is computed using the Binet formula.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::fibonacci
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `fibonacci[cond](x, ...)` is equivalent to `if_else(cond,fibonacci(x, ...),x)`
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
  //! @include{lineno} doc/core/fibonacci.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fibonacci_, fibonacci);
}

#include <eve/module/real/combinatorial/function/regular/generic/fibonacci.hpp>
