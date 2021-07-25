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
  //! @addtogroup arithmetic
  //! @{
  //! @var bound
  //!
  //! @brief Callable object computing the bound operation.
  //!
  //! **Required header:** `#include <eve/function/bound.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the bound operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U> auto operator()( T x,U y
  //!                                             , range_ctrl b, range_ctrl s) const noexcept
  //!   requires (compatible_values< T, U);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](../../concepts.html#value)
  //!
  //!`b`, `c`:   range_ctrl values
  //!
  //! **Return value**
  //!
  //! return a bound for `x` and `y` that can be min max absolute_min or absolute_max according to b,
  //! with a sign given by the choice of s that can be sign_from_first, sign_from_cmp, sign_clear or sign_set
  //!
  //!The result type is the [compatibility result](../../concept.html#compatibility) of the two first parameters.
  //!
  //!@warning
  //!   If any element of the inputs is a `Nan`, the corresponding output element is system-dependent.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::bound
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `bound[cond](x, ...)` is equivalent to `if_else(cond,bound(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/bound.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(bound_, bound);
}

#include <eve/module/real/core/function/regular/generic/bound.hpp>

// #if defined(EVE_INCLUDE_X86_HEADER)
// #  include <eve/module/real/core/function/regular/simd/x86/bound.hpp>
// #endif
