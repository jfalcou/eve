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
  //! @var cyl_bessel_in
  //!
  //! @brief Callable object computing the cyl_bessel_in function,  \f$ I_{n}(x)=\left(\frac12z\right)^n\sum_{k=0}^{\infty}{\frac{(x^2/4)^k}{k!\,\Gamma (k+n +1)}}\f$.
  //!
  //! **Required header:** `#include <eve/function/cyl_bessel_in.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the cyl_bessel_in function                                 |
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
  //!  \f$\displaystyle I_{n}(x)=\left(\frac12z\right)^n\sum_{k=0}^{\infty}{\frac{(x^2/4)^k}{k!\,\Gamma (k+n +1)}}\f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which \f$ y(0) = 0\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/cyl_bessel_in.hpp>`
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_in)(n, x)` computes the derivative of the function at `x`.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/cyl_bessel_in.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_in_, cyl_bessel_in);
}

#include <eve/module/real/special/function/regular/generic/cyl_bessel_in.hpp>
