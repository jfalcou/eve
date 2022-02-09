//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var bit_andnot
  //!
  //! @brief Callable object computing the bitwise ANDNOT operation.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the bitwise ANDNOT operation   |
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
  //! * For two parameters it computes the  bitwise ANDNOT of the two parameters
  //! * For more than two parameters the call is  semantically equivalent to to `bit_andnot(a0, bit_or(xs...))`
  //!
  //!@warning
  //!  the call `bit_andnot(x, y)` is semantically equivalent to `x & ~y` if `x` or  `y`
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
  //!  Higher-order function generating a masked version of eve::bit_andnot
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bit_andnot[cond](x, ...)` is equivalent to `if_else(cond,bit_andnot(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/bit_andnot.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bit_andnot_, bit_andnot);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/bit_andnot.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/bit_andnot.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_andnot.hpp>
#endif
