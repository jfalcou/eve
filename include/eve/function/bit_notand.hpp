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
  //! @var bit_notand
  //!
  //! @brief Callable object computing the bitwise NOTAND operation.
  //!
  //! **Required header:** `#include <eve/function/bit_notand.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the bitwise NOTAND operation   |
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
  //! [bitwise operations semantic](@ref glossary_bitwise).
  //! * For two parameters it computes the  bitwise NOTAND of the two parameters
  //! * For more than two parameters the call is  semantically equivalent to to `bit_notand(a0, bit_and(xs...))`
  //!
  //!@warning
  //!  the call `bit_notand(x, y)` is semantically equivalent to `~x & y` if `x` or  `y`
  //!  is an  [simd value](@ref eve::simd_value), but the pure scalar calls imply the original C++ operators
  //!  an may not exist due to C++ limitations.<br> Moreover if an hardware intrinsic exists,  the infix syntax
  //!  will not be able to use it.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bit_notand
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bit_notand[cond](x, ...)` is equivalent to `if_else(cond,bit_notand(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/bit_notand.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_notand_, bit_notand);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/bit_notand.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/bit_notand.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/real/core/function/regular/simd/ppc/bit_notand.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/real/core/function/regular/simd/arm/neon/bit_notand.hpp>
#endif
