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
  //! @var horner
  //!
  //! @brief Callable object computing the horner operation.
  //!
  //! **Required header:** `#include <eve/function/horner.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | evaluate a polynomial using the horner algorithm           |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x, value auto... args) const noexcept;
  //!  auto operator()(value auto x, range auto r) const noexcept;
  //!  auto operator()(value auto x, std::inputiterator auto first, std::inputiterator auto sentinel) const noexcept;
  //!  auto operator()(value auto x, callable_one_ const & o, value auto... args) const noexcept;
  //!  auto operator()(value auto x, callable_one_ const & o, range auto r) const noexcept;
  //!  auto operator()(value auto x, callable_one_ const & o, std::inputiterator auto first, std::inputiterator auto sentinel) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`x`:   [value x](@ref eve::value).
  //!
  //!`o`:   [callable_one_ ](@ref eve::value). Put eve::one here to have an unitary polynomial and a small optimization
  //!
  //!`args`:   [values ](@ref eve::value) expansion pack associated to \f$(a_i)_{i_0\le i \le n}\f$. \f$i_0\f$ is 1 if o is present else 0
  //!
  //!`r`:   [values ](@ref eve::value) Range containing the coefficients in the same conditions
  //!
  //!`first`, `sentinel`:   std::input_iterator conforming pair of iterators through the coefficients in the same conditions
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of polynomial function(s)
  //!represented by the coefficients in decreasing power order at `x`.
  //!
  //!The result type is of the compatibility type of the  coefficients and the evaluation value `x`.
  //!
  //!@warning
  //!   If the coefficients are simd values of cardinal N, this means you simultaneously compute the values of N polynomials.
  //!   *  If x is scalar, the polynomials are all computed at the same point
  //!   *  If x is simd, the nth polynomial is computed on the nth value of x
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::horner
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `horner[cond](x, ...)` is equivalent to `if_else(cond,horner(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/horner.hpp>`
  //!
  //!     The expression `pedantic(horner)(...)` computes the result using `pedantic(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!
  //!  * eve::numeric
  //!
  //!     **Required header:** `#include <eve/function/numeric/horner.hpp>`
  //!
  //!     The expression `numeric(horner)(...)` computes the result using `numeric(fma)(a,x,b)` for `a*x+b` instead of
  //!      `fma(a,x,b)`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/horner.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(horner_, horner);
}

#include <eve/module/real/polynomial/function/regular/generic/horner.hpp>
