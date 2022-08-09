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
  //! @var hypot
  //!
  //! @brief Callable object computing the hypot operation.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the hypot operation                                        |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( floating_real_value auto x, floating_real_value auto... args ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `args`:   [floating real values](@ref eve::floating_real_value)
  //!
  //! **Return value**
  //!
  //!The square root of the sum of the squared absolute values of the parameters.
  //!
  //!The result type is the [common compatible type](@ref common_compatible) of the three parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::hypot
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `hypot[cond](x, ...)` is equivalent to `if_else(cond,hypot(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!
  //!     The call `pedantic(hypot)(x,args...)`  computes the square root of the sum of the squares of the parameters
  //!      without undue overflow or underflow at intermediate stages of the computation
  //!      and can be more accurate than the non-decorated call.
  //!
  //!      Morever it returns \f$\infty\f$ as soon as one of its parameter is infinite, regardless of possible `Nan` values.
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
  //!
  //!
  //!     The expression `diff_< N >(hypot)(x,args...)` computes the partial
  //!      derivativ of the function relative to its Nth parameter. The returned value is 0 if N is
  //!      greater that the actual number of parameters, otherwise it is the
  //!      `N`th parameter value divided by the `hypot` value.
  //!
  //!  !!! Warning
  //!      This is only available for floating point entries.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/hypot.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(hypot_, hypot);
}

#include <eve/module/math/regular/impl/hypot.hpp>
