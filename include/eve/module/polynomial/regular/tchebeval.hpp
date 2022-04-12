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
  //! | `operator()` | evaluate a polynomial using the tchebeval algorithm           |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x, value auto... args) const noexcept;
  //!  auto operator()(value auto x, std::ranges::bidectional_range auto r) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`x`:   [value x](@ref eve::value).
  //!
  //!`args`:   [values ](@ref eve::value) expansion pack associated to \f$(a_i)_{i_0\le i \le n}\f$. \f$i_0\f$ is 1 if o is present else 0
  //!
  //!`r`:   [values ](@ref eve::value) Range containing the coefficients in the same conditions
  //!
  //!`first`, `sentinel`:   std::input_iterator conforming pair of iterators through the coefficients in the same conditions
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) the value of tchebytchev polynomial function
  //!represented by the coefficients in increasing index order at `x`.
  //!
  //!I.e if \f$c_0, ...c_{n-1}\f$ are the \fn\f$ given coefficients, the object function computes:
  //! \f$\displaymath c_0/2+\sum_1^n c_i T_i(x)\f$,  where the T_i are the n first tchebytchev polynomials
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
