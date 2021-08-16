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
  //! @var log1p
  //!
  //! @brief Callable object computing the natural logarithm of \f$1+x\f$: \f$\log(1+x)\f$.
  //!
  //! **Required header:** `#include <eve/function/log1p.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of the natural logarithm of \f$1+x\f$   |
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
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](@ref glossary_elementwise) the natural log1parithm  of `1+x`
  //!This function is more precise than the expression `log(1+x)` if arg is close to zero.
  //!
  //!In partucular, for floating inputs:
  //!
  //!   * If the element is \f$-1\f$, \f$-\infty\f$ is returned.
  //!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!   * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
  //!   * If the element is less than -1, `NaN` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::log1p
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `log1p[cond](x, ...)` is equivalent to `if_else(cond,log1p(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/log1p.hpp>`
  //!
  //!     The expression `diff(log1p)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/log1p.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(log1p_, log1p);
}

#include <eve/module/real/math/function/regular/generic/log1p.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/math/function/regular/simd/x86/log1p.hpp>
#endif
