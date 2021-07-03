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
  //! @addtogroup logical
  //! @{
  //! @var logical_xor
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/logical_xor.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the logical XOR operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical XOR operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //!
  //!
  //! **Return value**
  //!
  //!Computes  logical XOR of the two parameters following the
  //![logical operations semantic](../../../glossary.html#Logical).
  //!
  //!the call `logical_xor(x, y)` is semantically equivalent to `(x && !y) || (!x && y)`.
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::logical_xor
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `logical_xor[cond](x, ...)` is equivalent to `if_else(cond,logical_xor(x, ...),x)`
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
  //! @include{lineno} doc/core/logical_xor.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(logical_xor_, logical_xor);
}

#include <eve/module/real/core/function/regular/generic/logical_xor.hpp>

