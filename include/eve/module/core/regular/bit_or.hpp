//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var bit_or
  //!
  //! @brief Callable object computing the bitwise OR operation.
  //!
  //! **Required header:** `#include <eve/function/bit_or.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the bitwise OR operation   |
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
  //! [elementwise](@ref glossary_elementwise) bitwise OR of a0 and all `xs` following the
  //! [bitwise operations semantic](@ref glossary_bitwise).
  //!
  //!@warning
  //!   Although the infix notation with `|` is supported for two parameters, the `|` operator on
  //!   standard scalar types is the original one and so can lead to automatic promotion and due to C++
  //!   limitation is not available for floating point scalar entries.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bit_or
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bit_or[cond](x, ...)` is equivalent to `if_else(cond,bit_or(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/bit_or.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_or_, bit_or);
}

#include <eve/module/core/regular/impl/bit_or.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_or.hpp>
#endif
