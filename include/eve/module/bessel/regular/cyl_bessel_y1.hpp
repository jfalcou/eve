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
  //! @var cyl_bessel_y1
  //!
  //! @brief Callable object computing \f$ Y_1(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}{(\tau^2-1)^{3/2}}\,\mathrm{d}\tau\f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the cyl_bessel_y1 function of the second kind              |
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
  //!Computes  [elementwise](@ref glossary_elementwise) the value of
  //!
  //! \f$\displaystyle Y_1(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}{(\tau^2-1)^{3/2}}\,\mathrm{d}\tau\f$.
  //!
  //! It is a solution of \f$ x^{2}y''+xy'+(x^2-1)y=0\f$ for which \f$ y(0) = \infty\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_y1)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/cyl_bessel_y1.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_y1_, cyl_bessel_y1);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_y1.hpp>
