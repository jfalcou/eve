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
  //! @addtogroup special
  //! @{
  //! @var gamma_p
  //!
  //! @brief Callable object computing the normalized lower incomplete \f$\Gamma\f$ function :
  //!        \f$\displaystyle \frac{1}{\Gamma(x)}\int_0^{y} t^{x-1}e^{-t}\mbox{d}t\f$
  //!
  //! **Required header:** #include <eve/module/special.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the gamma_p operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( floating_real_value auto x, floating_real_value auto y) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) computes the normalized lower incomplete \f$\Gamma\f$ function :
  //! \f$\displaystyle \frac{1}{\Gamma(x)}\int_0^{y} t^{x-1}e^{-t}\mbox{d}t\f$
  //!
  //! The result type is the [common compatible type](@ref common_compatible) of the two parameters.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::gamma_p
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `gamma_p[cond](x, ...)` is equivalent to `if_else(cond,gamma_p(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/special/gamma_p.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(gamma_p_, gamma_p);
}

#include <eve/module/special/regular/impl/gamma_p.hpp>
