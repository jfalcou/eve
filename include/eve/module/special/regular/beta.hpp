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
  //! @addtogroup special
  //! @{
  //! @var beta
  //!
  //! @brief Callable object computing the beta function. \f$\mbox{B}(x,y)=\int_0^1 t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
  //!
  //! **Required header:** `#include <eve/function/beta.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the beta operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_value T, floating_value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) \f$\displaystyle \frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\f$.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::beta
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `beta[cond](x, ...)` is equivalent to `if_else(cond,beta(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //! * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
  //!:   **Required header:** `#include <eve/function/diff/beta.hpp>`
  //!
  //!:   The expression `diff_1st(beta)(x,y)` and `diff_2nd(beta)(x,y)` computes the partial
  //!    derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ \mbox{B}(x,y)\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/beta.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(beta_, beta);
}

#include <eve/module/special/regular/impl/beta.hpp>
