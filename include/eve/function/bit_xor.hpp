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
  //! @addtogroup bits
  //! @{
  //! @var bit_xor
  //!
  //! @brief Callable object computing the bitwise XOR operation.
  //!
  //! **Required header:** `#include <eve/function/bit_xor.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the bitwise XOR operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::value auto a0, eve::value auto ... xs) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! a0, `xs`:  Instances of eve::value
  //!
  //! **Return value**
  //!
  //! A value of the same type as a0 containing the
  //! [elementwise](@ref glossary_elementwise) bitwise XOR of a0 and all `xs` following the
  //! [bitwise operations semantic](../../../glossary.html#Bitwise).
  //!
  //!@warning
  //!   Although the infix notation with `^` is supported for two parameters, the `^` operator on
  //!   standard scalar types is the original one and so can lead to automatic promotion and due to C++
  //!   limitation is not available for floating point scalar entries.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bit_xor
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bit_xor[cond](x, ...)` is equivalent to `if_else(cond,bit_xor(x, ...),x)`
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
  //! @include{lineno} doc/core/bit_xor.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_xor_, bit_xor);
}

#include <eve/module/real/core/function/regular/generic/bit_xor.hpp>
