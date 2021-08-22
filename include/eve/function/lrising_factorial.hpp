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
  //! @var lrising_factorial
  //!
  //! @brief Callable object computing the lrising_factorial function i.e.
  //! \f$\log\left(\frac{\Gamma(x+a)}{\Gamma(x)}\right)\f$.
  //!
  //! **Required header:** `#include <eve/function/lrising_factorial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | lrising_factorial operation                                |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value I, floating_value T > auto operator()( I a, T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`a`:   [real_value](@ref eve::real_value).`a` must be positive or the result is Nan
  //!
  //!`x`:   [floating real value](@ref eve::value). `a+x` must be positive or the result is Nan
  //!
  //! **Return value**
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::lrising_factorial
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `lrising_factorial[cond](x, ...)` is equivalent to `if_else(cond,lrising_factorial(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::raw
  //!
  //!     **Required header:** `#include <eve/function/lrising_factorial.hpp>`
  //!
  //!     The expression `raw(lrising_factorial)(a,x)` uses the crude formula with all its limitations and
  //!      inacurracies and return a Nan if `a` and `a+x` are not both positive
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/lrising_factorial.hpp>`
  //!
  //!     The expression `pedantic(lrising_factorial)(a,x)` uses reflection tricks and computes the function
  //!       for all real `a` and `x`, and in fact computes the logarithm of the absolute value of the Pochammer
  //!       symbol \f$\log\left|\frac{\Gamma(x+a)}{\Gamma(x)}\right|\f$ returning nan if the result is really undefined.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/lrising_factorial.hpp>`
  //!
  //!     The expression `diff_1st(lrising_factorial)(a,x)` and `diff_2nd(lrising_factorial)(a,x)` computes
  //!      the derivative of the function relative to the first or second parameter respectively.
  //!
  //!      These decorators can be combined to the other available ones : for instance the call
  //!
  //!      `pedantic(diff_1st)(lrising_factorial)(a,x)`
  //!
  //!      will compute the derivative of `pedantic(lrising_factorial)` relative to the first parameter.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/lrising_factorial.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(lrising_factorial_, lrising_factorial);
}

#include <eve/module/real/combinatorial/function/regular/generic/lrising_factorial.hpp>
