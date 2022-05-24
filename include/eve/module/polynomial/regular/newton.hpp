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
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x, range auto c, range auto n) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`x`:   [value x](@ref eve::value).
  //!
  //!`c`, `n``:   [values ](@ref eve::value) Range containing respectively the coefficients and the nodes
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
