//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup special
  //! @{
  //! @var airy_ai
  //!
  //! @brief Callable object computing the airy_ai function.
  //!
  //! **Required header:** `#include <eve/function/airy_ai.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the airy_ai function                                       |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating_real_value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //! Computes  [elementwise](@ref glossary_elementwise) the value of
  //! \f$ Ai(x)=\frac1{\pi} \int_{0}^{\infty}\cos \left( \frac{t^3}{3}+xt \right) \,dt\f$.
  //!
  //!  It is the solution of the differential equation \f$y''-xy = 0\f$ satisfying
  //! \f$Ai(0) = \frac1{3^{2/3}\Gamma(2/3)}\f$ and \f$Ai'(0) =\frac1{3^{1/3}\Gamma(1/3)}\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/airy_ai.hpp>`
  //!
  //!     The expression `eve::diff(eve::airy_ai)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/airy_ai.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(airy_ai_, airy_ai);
}

#include <eve/module/real/special/function/regular/generic/airy_ai.hpp>
