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
  //! @var jacobi
  //!
  //! @brief Callable object evaluating the jacobi polynomial: \f$P^{\alpha, \beta}_n(x)\f$
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the jacobi operation                                       |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto n,  floating_value alpha,  floating_value beta, floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [value](@ref eve::value). Must be a flint
  //!
  //!`x`:   [floating value](@ref eve::floating_value).
  //!
  //!`alpha`, `beta`:   [floating valuse](@ref eve::floating_value).
  //!
  //! **Return value**
  //!
  //! \f$P^{\alpha, \beta}_n(x)\f$
  //!
  //!The result type is of the [common compatible type](@ref common_compatible) type of the  parameters.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `diff(jacobi)(...,x)` computes the derivative of the function relative to `x`.
  //!
  //!     The expression `diff(jacobi)(...,x,k)` computes the derivative of order k of the function relative to `x`.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/polynomial/jacobi.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(jacobi_, jacobi);
}

#include <eve/module/polynomial/regular/impl/jacobi.hpp>
