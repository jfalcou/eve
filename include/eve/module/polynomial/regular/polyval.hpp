//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup polynomial
  //! @{
  //! @var polyval
  //!
  //! @brief Callable object computing the polyval operation.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | compute the (nth) polyval of a polynomial               |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template < floating_scalar_value T> auto operator()(polynom<T> p, like<T> x) noexcept;
  //!  template < floating_scalar_value T> auto operator()(monom<T> p, like<T> x) noexcept;
  //!  template < floating_scalar_value T, range R> auto operator()(polynom<T> p, R x) noexcept;
  //!  template < floating_scalar_value T, range R> auto operator()(monom<T> p, R x) noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! **Parameters**
  //!
  //!`p`:   polynomial or monomial
  //!
  //!`x`:   evaluation data
  //!
  //! **Return value**
  //!    - the calls return the evaluation of p at all elements of x,  the element type of x must be T.
  //!
  //!    - you can also use the usual Mathematical call p(x),  except if you need to replace x by the result.
  //!      (see the inplace decorator below)
  //!
  //! #### Supported decorators
  //!
  //!  * eve::inplace
  //!
  //!     The expression `inplace(polyval)(p, x)` replaces x by the values of p(x).
  //!     The paramater x is taken by reference (must be non const) and the operator returns void.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/polynomial_polyval.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(polyval_, polyval);
}
