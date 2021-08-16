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
  //! @addtogroup special
  //! @{
  //! @var exp_int
  //!
  //! @brief Callable object computing the exponential integral \f$\displaystyle \mbox{E}_{n}(x)=\int_0^\infty \frac{e^{-xt}}{t^{n}} \mbox{d}t\f$.
  //!
  //! **Required header:** `#include <eve/function/exp_int.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the exp_int operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, floating_value U > auto operator()( T n, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](@ref eve::value).
  //!
  //!`x`:   [floating value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) exponential integral
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!If the first parameter inot an integral value it must be a flint, otherwise the result is Nan.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::exp_int
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `exp_int[cond](x, ...)` is equivalent to `if_else(cond,exp_int(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/exp_int.hpp>`
  //!
  //!     The expression `diff(exp_int)(n,x)` computes the derivative (relative to the second parameter)
  //!      of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/exp_int.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exp_int_, exp_int);
}

#include <eve/module/real/special/function/regular/generic/exp_int.hpp>
