//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math
  //! @{
  //! @var geommean
  //!
  //! @brief Callable object computing the mid-point operation.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the mid-point operation                                    |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( floating_value auto x, floating_value auto y ) const noexcept;
  //!  auto operator()( floating_value auto x, floating_value auto... args ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
 //! ---
  //!
  //! **Parameters**
  //!
  //!`x`, `y` or `x`, `args ...`:   [floating values](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!For two parameters \f$\sqrt{xy}\f$. No overflow occurs.
  //!
  //!For more than two parameters \f$\sqrt[n]{x_1x_2...x_n}\f$
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the parameters.
  //!
  //!@warning
  //!    for floating_real_value input types
  //!    * if the number of parameters is even and the product of the parameters is srictly negative the result is a Nan.
  //!    * if the number of parameters is odd the result has the sign of the product of the parameters
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::geommean
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `geommean[cond](x, ...)` is equivalent to `if_else(cond,geommean(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `diff_nth`
  //!
  //!
  //!     The expression `diff_nth< N >(geommean)(x,args...)` computes the partial
  //!      derivative of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise it is similar to `geommean(x1,x2,...,xn)/(n*xN)`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/geommean.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(geommean_, geommean);
}

#include <eve/module/math/regular/impl/geommean.hpp>
