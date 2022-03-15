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
  //! @var cyl_bessel_i0
  //!
  //! @brief Callable object computing \f$ I_0(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\,\mathrm{d}\tau\f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the modified cyl_bessel_i0 function of the first kind      |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   positive [floating_real_value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Computes  [elementwise](@ref glossary_elementwise) the value of
  //!  \f$ \displaystyle I_0(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\,\mathrm{d}\tau\f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'-x^2y=0\f$ for which \f$ y(0) = 0\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_i0)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/cyl_bessel_i0.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_i0_, cyl_bessel_i0);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_i0.hpp>
