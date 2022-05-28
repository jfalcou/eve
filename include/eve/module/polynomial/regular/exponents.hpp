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
  //! @var exponents
  //!
  //! @brief Callable object computing the exponents operation.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | compute the exponents of a polynomial                          |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_scalar_value> auto operator()(polynomial<T> p) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`p`:   polynomial.
  //!
  //! **Return value**
  //!    - Returns the exponents of non nul coefficients of a polynom in decreasing power order
  //!
  //!@warning You can reconstruct the polynomial only if you also have the vector of
  //!@ values peertaining to each exponent.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/polynomial_exponents.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exponents_, exponents);
}
