//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/shl.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var bit_shl
  //!
  //! @brief Callable object computing the logical left shift operation.
  //!
  //! **Required header:** `#include <eve/function/bit_shl.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical left shift operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, integral_real_value U > auto operator()( T x, U n ) const noexcept requires bit_compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   An instance of a \ref eve::value.
  //!
  //!`n`:   An instance of an [integral_value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes the [element-wise](@ref glossary_elementwise) logical left shift of the first parameter
  //!by the second one.
  //!
  //!the call `bit_shl(x, n)` is equivalent to `x << n` if `x`  is an  \link eve::simd_value simd value\endlink.
  //!
  //!The types must share the same cardinal or be scalar and if \f$N\f$ is the size in bits  of the element type of `T`,
  //!all elements of n must belong to the
  //!interval: \f$[0, N[\f$ or the result is undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bit_shl
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bit_shl[cond](x, ...)` is equivalent to `if_else(cond,bit_shl(x, ...),x)`
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
  //! @include{lineno} doc/core/bit_shl.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_ALIAS_CALLABLE(shl_, bit_shl);
}
