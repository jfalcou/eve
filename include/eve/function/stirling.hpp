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
  //! @var stirling
  //!
  //! @brief Callable object computing an approximation of the
  //!        \f$\Gamma\f$ function by \f$\displaystyle \Gamma(x) \approx \sqrt{2 \pi} x^{x-\frac12} e^{-x} \left( 1 + \frac1{x} P(\frac1{x})\right)\f$,
  //!        where \f$P\f$ is a polynomial.
  //!
  //! **Required header:** `#include <eve/function/stirling.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the stirling operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, floating_value U > auto operator()( Tx ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns [elementwise](@ref glossary_elementwise) \f$\sqrt{2 \pi} x^{x-\frac12} e^{-x} \left( 1 + \frac1{x} P(\frac1{x})\right)\f$
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::stirling
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `stirling[cond](x, ...)` is equivalent to `if_else(cond,stirling(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/stirling.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(stirling_, stirling);
}

#include <eve/module/real/special/function/regular/generic/stirling.hpp>
