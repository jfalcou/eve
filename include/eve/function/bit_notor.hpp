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
  //! @var bit_notor
  //!
  //! @brief Callable object computing the bitwise NOTOR operation.
  //!
  //! **Required header:** `#include <eve/function/bit_notor.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the bitwise NOTOR operation   |
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
  //! The value returned is of same type as `a0` and follows the
  //! [bitwise operations semantic](../../../glossary.html#Bitwise).
  //! * For two parameters it computes the  bitwise NOTOR of the two parameters
  //! * For more than two parameters the call is  semantically equivalent to to `bit_notor(a0, bit_or(xs...))`
  //!
  //!@warning
  //!  the call `bit_notor(x, y)` is semantically equivalent to `~x | y` if `x` or  `y`
  //!  is an  [simd value](@ref eve::value), but the pure scalar calls imply the original C++ operators
  //!  an may not exist due to C++ limitations.<br> Moreover if an hardware intrinsic exists,  the infix syntax
  //!  will not be able to use it.
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bit_notor
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bit_notor[cond](x, ...)` is equivalent to `if_else(cond,bit_notor(x, ...),x)`
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
  //! @include{lineno} doc/core/bit_notor.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_notor_, bit_notor);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/bit_notor.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/bit_notor.hpp>
#endif
