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
  //! @var newton
  //!
  //! @brief Callable object computing the newton operation: \f$\sum_{i = 0}^n c_i\prod_{j = 0}^i (x-n_i)\f$.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the newton operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x, range auto c, range auto n) const noexcept;
  //!  auto operator()(value x, std::inputiterator auto firstcoef, std::inputiterator auto sentinel, std::inputiterator auto firstnode) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`x`:   [value x](@ref eve::value).
  //!
  //!`c`, `n``:   [values ](@ref eve::value) Range containing the coefficients
  //!
  //!`firstcoef`, `sentinel`,`firstnode`:   std::input_iterator conforming pair of iterators through the coefficients and start of the nodes
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of polynomial function(s)
  //!represented in newton form by the coefficients and the nodes.
  //!
  //!The result type is of the compatibility type of the  coefficients and the evaluation value `x`.
  //!
  //!@warning
  //!   If the coefficients are simd values of cardinal N, this means you compute the values of N polynomials.
  //!   * If x is scalar, the polynomials are all computed at the same point
  //!   * If x is simd, the nth polynomial is computed on the nth value of x
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::newton
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `newton[cond](x, ...)` is equivalent to `if_else(cond,newton(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!
  //!     The expression `pedantic(newton)(...)` computes the result using `pedantic(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!
  //!  * eve::numeric
  //!
  //!
  //!     The expression `numeric(newton)(...)` computes the result using `numeric(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/newton.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(newton_, newton);
}

#include <eve/module/polynomial/regular/impl/newton.hpp>
