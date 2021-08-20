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
  //! @addtogroup arithmetic
  //! @{
  //! @var arg
  //!
  //! @brief Callable object computing the phase angle (in radians).
  //!
  //! **Required header:** `#include <eve/function/arg.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the phase angle (in radians)   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<floating_value T> auto operator()(T x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating value](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!For each  [element](@ref glossary_element) of the input the phase angle is returned:
  //!
  //!  If the input type is a [floating real value](@ref eve::floating_real_value):
  //!
  //!    *  if the bit of sign of the entry [element](@ref glossary_elementwise) is not set, \f$0\f$ is returned.
  //!    *  if the bit of sign of the entry [element](@ref glossary_elementwise) is set, \f$\pi\f$ is returned.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::arg
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `arg[cond](x, ...)` is equivalent to `if_else(cond,arg(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  <span class="smallskip"></span>
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/arg.hpp>`
  //!
  //!     With this decorator the function returns a Nan element for each corresponding Nan entry element.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/arg.hpp>`
  //!
  //!     The expression `diff(arg)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/arg.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(arg_, arg);
}

#include <eve/module/real/core/function/regular/generic/arg.hpp>
