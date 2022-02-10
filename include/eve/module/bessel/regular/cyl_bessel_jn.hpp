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
  //! @var cyl_bessel_jn
  //!
  //! @brief Callable object computing the cyl_bessel_jn function,  \f$ J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}{\left({x \over 2}\right)}^{2p+n }\f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the cyl_bessel_jn function                                 |
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
  //!`x`:   [floating_real_value](@ref eve::floating_real_value). if n is non an integral value, a negative entry will return a Nan.
  //!
  //! **Return value**
  //!
  //! \f$\displaystyle J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}{\left({x \over 2}\right)}^{2p+n }\f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which \f$ y(0) = 0\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_jn)(n, x)` computes the derivative of the function at `x`.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/cyl_bessel_jn.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_jn_, cyl_bessel_jn);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_jn.hpp>
