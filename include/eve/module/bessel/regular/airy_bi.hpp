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
  //! @addtogroup bessel
  //! @{
  //! @var airy_bi
  //!
  //! @brief Callable object computing the airy_bi function.
  //!
  //! **Required header:** `#include <eve/function/airy_bi.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the airy_bi function                                       |
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
  //! \f$ Bi(x) = \frac1{\pi}\int_{0}^{\infty} \left[\exp\left(-{\frac{t^{3}}{3}}+xt\right)+\sin\left({\frac{t^{3}}{3}}+xt\right)\,\right]dt\f$.
  //!
  //!  It is the solution of the differential equation \f$y''-xy = 0\f$ satisfying
  //! \f$Bi(0) = \frac1{3^{1/6}\Gamma(2/3)}\f$ and
  //! \f$Bi'(0) =\frac{3^{1/6}}{\Gamma(1/3)}\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/airy_bi.hpp>`
  //!
  //!     The expression `eve::diff(eve::airy_bi)(x)` computes the derivative of the function at `x`.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/airy_bi.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(airy_bi_, airy_bi);
}

#include <eve/module/bessel/regular/impl/airy_bi.hpp>
