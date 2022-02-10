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
  //! @var lbeta
  //!
  //! @brief Callable object computing the logarithm of the beta function.
  //!
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the lbeta operation   |
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
  //!Returns [elementwise](@ref glossary_elementwise) \f$\displaystyle \log\left(\frac{\Gamma(x)\Gamma(y)}{\Gamma(x+y)}\right)\f$.
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::lbeta
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `lbeta[cond](x, ...)` is equivalent to `if_else(cond,lbeta(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!
  //!  *  eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_nth
  //!
  //!
  //!    The expression `derivative_1st(lbeta)(x,y)` and `derivative_2nd(lbeta)(x,y)` computes the partial
  //!    derivatives of \f$f\f$, where \f$f\f$ is the function \f$(x,y) \rightarrow \ \log(\mbox{B}(x,y))\f$.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/special/lbeta.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(lbeta_, lbeta);
}

#include <eve/module/special/regular/impl/lbeta.hpp>
