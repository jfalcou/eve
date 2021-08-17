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
  //! @addtogroup hyperbolic
  //! @{
  //! @var sech
  //!
  //! @brief Callable object computing sech: \f$\frac2{e^x-e^{-x}}\f$.
  //!
  //! **Required header:** `#include <eve/function/sech.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of sech   |
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
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) hyperbolic secant of the input.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, 1 is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$+0\f$ is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::sech
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `sech[cond](x, ...)` is equivalent to `if_else(cond,sech(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/sech.hpp>`
  //!
  //!     The expression `diff(sech)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/sech.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sech_, sech);
}

#include <eve/module/real/math/function/regular/generic/sech.hpp>
