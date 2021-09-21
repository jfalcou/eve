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
  //! @addtogroup exponential
  //! @{
  //! @var expm1
  //!
  //! @brief Callable object computing \f$e^x-1\f$.
  //!
  //! **Required header:** `#include <eve/function/expm1.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of expm1   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( floating_real_value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) exponential input minus one, with good accuracy, even for small values of `x`.
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned
  //!   * If the element is \f$-\infty\f$, \f$-1\f$ is returned
  //!   * If the element is \f$\infty\f$, \f$\infty\f$ is returned
  //!   * If the element is a `NaN`, `NaN` is returned
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::expm1
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `expm1[cond](x, ...)` is equivalent to `if_else(cond,expm1(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/expm1.hpp>`
  //!
  //!     The expression `diff(expm1)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/expm1.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(expm1_, expm1);
}

#include <eve/module/real/math/function/regular/generic/expm1.hpp>
