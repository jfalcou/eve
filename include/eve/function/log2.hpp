//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup exponential
  //! @{
  //! @var log2
  //!
  //! @brief Callable object computing the base 2 logarithm: \f$\log_2 x\f$.
  //!
  //! **Required header:** `#include <eve/function/log2.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the base 2 logarithm   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](../../../glossary.html#elment-wise) the base 2 logarithm  of `x`
  //!In partucular, for floating inputs:
  //!
  //!   * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
  //!   * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!   * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
  //!   * If the element is less than 0, `NaN` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::log2
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `log2[cond](x, ...)` is equivalent to `if_else(cond,log2(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `diff`
  //!
  //!     **Required header:** `#include <eve/function/diff/log2.hpp>`
  //!
  //!     The expression `diff(log2)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/log2.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log2_, log2);
}

#include <eve/module/real/math/function/regular/generic/log2.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/math/function/regular/simd/x86/log2.hpp>
#endif
