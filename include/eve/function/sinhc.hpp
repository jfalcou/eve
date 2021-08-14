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
  //! @var sinhc
  //!
  //! @brief Callable object computing sinhc: \f$\frac{e^x-e^{-x}}{2x}\f$.
  //!
  //! **Required header:** `#include <eve/function/sinhc.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of sinhc   |
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
  //!`x`:   [floating real value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](@ref glossary_elementwise) hyperbolic sine of the input divided by the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::sinhc
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `sinhc[cond](x, ...)` is equivalent to `if_else(cond,sinhc(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/sinhc.hpp>`
  //!
  //!     The expression `diff(sinhc)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/sinhc.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sinhc_, sinhc);
}

#include <eve/module/real/math/function/regular/generic/sinhc.hpp>
