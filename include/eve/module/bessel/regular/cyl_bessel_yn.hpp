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
  //! @var cyl_bessel_yn
  //!
  //! @brief Callable object computing the cyl_bessel_yn function,  \f$ Y_{n}(x)=\frac{2(z/2)^{-n}}{\sqrt\pi\, \Gamma(1/2-n)}\int _{1}^{\infty}\frac{\cos x\tau}{(\tau^2-1)^{n+1/2}}\,\mathrm {d} \tau \f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the cyl_bessel_yn function of the second kind              |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value N, floating_real_value T  > auto operator()( N n, T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [real_value](@ref eve::real_value) order of the function (non necessarily integral)
  //!
  //!`x`:   positive [floating_real_value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //! \f$\displaystyle Y_{n}(x)=\frac{2(z/2)^{-n}}{\sqrt\pi\, \Gamma(1/2-n)}\int _{1}^{\infty}\frac{\cos x\tau}{(\tau^2-1)^{n+1/2}}\,\mathrm {d} \tau \f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which \f$ y(0) = \infty\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_yn)(n, x)` computes the derivative of the function at `x`.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/cyl_bessel_yn.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_yn_, cyl_bessel_yn);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_yn.hpp>
