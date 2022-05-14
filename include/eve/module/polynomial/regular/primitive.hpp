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
  //! @var primitive
  //!
  //! @brief Callable object computing the primitive operation.
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | compute the (nth) primitive of a polynomial               |
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
  //!`n`:   order of integration
  //!
  //!`all`:  if all is present a vector of polynomial containing all primitives from 0 to n is returned
  //!
  //! **Return value**
  //!    - the first call returns the polynomial primitive pf p null at 0
  //!    - the second call returns the  polynomial nth primitive pf p of valuation n (or -1 if p is null)
  //!    - the third call returns a vector of polynoms containing all these primitives from 0 to n.
  //!
  //! #### Supported decorators
  //!
  //!  * eve::inplace
  //!
  //!     The expression `inplace(primitive)(p)` or  `inplace(primitive)(p, n)` replaceq p
  //!     by the computed object value
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/polynomial_primitives.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(primitive_, primitive);
}
