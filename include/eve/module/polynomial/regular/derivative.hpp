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
  //! @var derivative
  //!
  //! @brief Callable object computing the derivative operation.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | compute the (nth) derivative of a polynomial               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_scalar_value> auto operator()(polynomial<T> p) const noexcept;
  //!  template < floating_scalar_value> auto operator()(polynomial<T> p, size_t n) const noexcept;
  //!  template < floating_scalar_value> auto operator()(polynomial<T> p, size_t n, callable_all_ const &);
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`p`:   polynomial.
  //!
  //!`n`:   order of derivation
  //!
  //!`all`:  if all is present a vector of polynomial containing all derivatives from 0 to n is returned
  //!
  //!
  //! **Return value**
  //!    - the first call returns the polynomial derivative pf p
  //!    - the second call returns the  polynomial nth derivative pf p
  //!    - the third call returns a vector of polynomial containing all derivatives from 0 to n.
  //!
  //! #### Supported decorators
  //!
  //!  * eve::inplace
  //!
  //!     The expression `inplace(derivative)(p)` or  `inplace(derivative)(p, n)` replace p by the computed value
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/polynomial_derivative.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(derivative_, derivative);
}

#include <eve/module/polynomial/regular/impl/derivative.hpp>
