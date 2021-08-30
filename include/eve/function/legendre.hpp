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
  //! @var legendre
  //!
  //! @brief Callable object evaluating the legendre functions.
  //!
  //! **Required header:** `#include <eve/function/legendre.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the legendre operation                                     |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( integral_value n, floating_value x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [real value](@ref eve::real_value). `n` must be a [flint](eve::is_flint) or the result is U.B.
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value). `x` must be in the \f$[-1, 1]\f$ interval or the result is nan.
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of the first kind Legendre polynomial of order `n` at `x`.
  //!
  //!The result type is of the [index compatible type](@ref index_compatible) type of the  parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::legendre
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `legendre[cond](x, ...)` is equivalent to `if_else(cond,legendre(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::p_kind, eve::q_kind
  //!
  //!     The expression `p_kind(legendre)(n,x)` is equivalent to `legendre(n,x)`.
  //!
  //!     The expression `q_kind(legendre)(n,x)` return the value at `x` of the second kind legendre function of order `n`.
  //!
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/legendre.hpp>`
  //!
  //!     The expression `diff(legendre)(...,x)` computes the derivative of the p_kind function relative to `x`.
  //!
  //!  * eve::successor
  //!
  //!     The expression `successor(legendre)(l, x, ln, lnm1)` implements the three term recurrence relation for the Legendre polynomials,
  //!     \f$\displaystyle \mbox{P}_{n+1} = \left((2l+1)\mbox{P}_{n}(x)-l\mbox{P}_{n-1}(x)\right)/(l+1)\f$
  //!     This object function can be used to create a sequence of values evaluated at the same `x` and for rising `l`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/legendre.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(legendre_, legendre);
}

#include <eve/module/real/polynomial/function/regular/generic/legendre.hpp>
