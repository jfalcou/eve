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
  //! @addtogroup polynomial
  //! @{
  //! @var laguerre
  //!
  //! @brief Callable object computing the laguerre operation:
  //! \f$\displaystyle \mbox{L}_{n} = \frac{e^x}{n!}\frac{d^n}{dx^n}(x^ne^{-x})\f$
  //! or the associated laguerre operation \f$\displaystyle \mbox{L}_{n}^{m} = (-1)^m\frac{d^m}{dx^m}\mbox{L}_{n+m}(x)\f$
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the laguerre operation                                     |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( integral_value auto n, floating_value auto x) const noexcept;
  //!  auto operator()( integral_value auto m, integral_value auto n, floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`,  `m`:   [integral real value](@ref eve::integral_real_value).
  //!
  //!`x`:   [floating value](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of the 'physicists' laguerre polynomial of order `n` at `x`,
  //!or if `m` is present the value of the associated laguerre polynomial.
  //!
  //!The result type is of the [common compatible type](@ref common_compatible) type of the  parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::laguerre
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `laguerre[cond](x, ...)` is equivalent to `if_else(cond,laguerre(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `diff(laguerre)(...,x)` computes the derivative of the function relative to `x`.
  //!
  //!  * eve::successor
  //!
  //!     The expression `successor(laguerre)(n, m, x, ln, lnm1)` implements the three term recurrence relation for the Laguerre polynomials,
  //!     \f$\displaystyle \mbox{L}_{n+1} = \left((2n+1-x)\mbox{L}_{n}-n\mbox{L}_{n-1}\right)/(n+1)\f$
  //!
  //!     The expression `successor(laguerre)(n, m, x, ln, lnmm1)` implements the three term recurrence relation for the Laguerre polynomials,
  //!     \f$\displaystyle \mbox{L}_{n+1}^m = \left((m+2n+1-x)\mbox{L}_{n}^{m}-(m+n)\mbox{L}_{n-1}^{m}\right)/(n+1)\f$
  //!
  //!     These object functions can be used to create a sequence of values evaluated at the same `x`, for the same `m`, and for rising `n`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/laguerre.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(laguerre_, laguerre);
}

#include <eve/module/polynomial/regular/impl/laguerre.hpp>
