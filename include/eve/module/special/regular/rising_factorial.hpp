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
  //! @addtogroup combinatorial
  //! @{
  //! @var rising_factorial
  //!
  //! @brief Callable object computing rising_factorial function i.e. \f$\frac{\Gamma(x+a)}{\Gamma(a)}\f$.
  //!
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | rising_factorial operation                                 |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( real_value auto a, floating_real_value x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`a`:   [value](@ref eve::value). `a` must be positive or the result is Nan
  //!
  //!`x`:   [floating value](@ref eve::value). `a+x` must be positive or the result is Nan
  //!
  //! **Return value**
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::rising_factorial
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `rising_factorial[cond](x, ...)` is equivalent to `if_else(cond,rising_factorial(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::raw
  //!
  //!
  //!     The expression `raw(rising_factorial)(a,x)` uses the crude formula with all its limitations and
  //!      inacurracies and return a Nan if `a` and `a+x` are not both positive
  //!
  //!  * eve::pedantic
  //!
  //!
  //!     The expression `pedantic(rising_factorial)(a,x)` uses reflection tricks and computes the function for all real `a` and `x`,
  //!      and in fact computes the Pochammer symbol  \f$x^{\overline a}=\frac{\Gamma(x+a)}{\Gamma(a)}\f$
  //!      returning nan if the result in really undefined.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
  //!
  //!     The expression `diff_1st(rising_factorial)(a,x)` and `diff_2nd(rising_factorial)(a,x)` computes
  //!      the derivative of the function relative to the first or second parameter respectively.
  //!
  //!      These decorators can be combined to the other available ones : for instance the call
  //!
  //!         `pedantic(diff_1st)(rising_factorial)(a,x)`
  //!
  //!      will compute the derivative of `pedantic(rising_factorial)` relative to the first parameter.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/combinatorial/rising_factorial.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(rising_factorial_, rising_factorial);
}

#include <eve/module/special/regular/impl/rising_factorial.hpp>
