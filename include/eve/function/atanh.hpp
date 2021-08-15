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
  //! @addtogroup hyperbolic
  //! @{
  //! @var atanh
  //!
  //! @brief Callable object computing atanh: \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
  //!
  //! **Required header:** `#include <eve/function/atanh.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of atanh   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](@ref glossary_elementwise) inverse hyperbolic cotangent of the input.
  //!The inverse hyperbolic sine is semantically equivalent to \f$\frac{1}{2}\log((1+x)/(1-x))\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!   * If the element is greater than one or a `NaN`, `NaN` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::atanh
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `atanh[cond](x, ...)` is equivalent to `if_else(cond,atanh(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/atanh.hpp>`
  //!
  //!     The expression `diff(atanh)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/atanh.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(atanh_, atanh);
}

#include <eve/module/real/math/function/regular/generic/atanh.hpp>
