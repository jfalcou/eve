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
  //! @var tchebeval
  //!
  //! @brief Callable object computing the tchebeval operation.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | evaluate a polynomial using the tchebeval algorithm        |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x, value auto... cs) const noexcept;
  //!  auto operator()(value auto x, range auto r) const noexcept;
  //!  auto operator()(value auto x, auto a,  auto b, auto r) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //!`a`, `b`:   [values](@ref eve::value). If present,  they are the bounds of the interval for which the tchebytchev polynomial
  //!       must be evaluated ( -1 and 1 by default). A change of variable \f$ x -> \frac{2x-a-b}{b-a} is internally performed.
  //!`
  //!`cs`:   [values ](@ref eve::value) expansion pack associated to the coefficients \f$(c_i)_{i_0\le i \lt n}\f$.
  //!
  //!`r`:   [values ](@ref eve::value) Range containing the coefficients in the same conditions
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of tchebytchev polynomial function
  //!represented by the coefficients in increasing index order at `x`.
  //!
  //!I.e if \f$c_0, ...c_{n-1}\f$ are the \f$n\f$ given coefficients, the object function computes:
  //! \f$\displaymath c_0/2+\sum_1^n c_i T_i(x)\f$,  where the T_i are the n first tchebytchev polynomials of first kind
  //!
  //!
  //!The result type is of the compatibility type of the  coefficients and the evaluation value `x`.
  //!
  //! The values are evaluted in linear \f$O(n)\f$ time.
  //!
  //!@warning
  //!   If the coefficients are simd values of cardinal N, this means you simultaneously compute the values of N polynomials.
  //!   *  If x is scalar, the polynomials are all computed at the same point
  //!   *  If x is simd, the nth polynomial is computed on the nth value of x
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/tchebeval.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(tchebeval_, tchebeval);
}

#include <eve/module/polynomial/regular/impl/tchebeval.hpp>
