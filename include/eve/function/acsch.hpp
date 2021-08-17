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
  //! @var acsch
  //!
  //! @brief Callable object computing acsch: \f$\log(1/x+\sqrt{1/x^2+1})\f$.
  //!
  //! **Required header:** `#include <eve/function/acsch.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of acsch   |
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
  //!Returns the [elementwise](@ref glossary_elementwise) inverse hyperbolic cosine of the input.
  //!The inverse hyperbolic sine is semantically equivalent to  \f$\log(1/x+\sqrt{1/x^2+1})\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm\infty\f$, \f$\pm0\f$ returned.
  //!   * If the element is \f$\pm1\f$, \f$\pm\infty\f$ is returned.
  //!   * If the element does not belong \f$]0,1[\f$, `NaN` is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::acsch
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `acsch[cond](x, ...)` is equivalent to `if_else(cond,acsch(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/acsch.hpp>`
  //!
  //!     The expression `diff(acsch)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/acsch.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(acsch_, acsch);
}

#include <eve/module/real/math/function/regular/generic/acsch.hpp>
