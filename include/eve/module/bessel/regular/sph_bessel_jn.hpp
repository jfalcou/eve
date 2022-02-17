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
  //! @var sph_bessel_jn
  //!
  //! @brief Callable object computing the sph_bessel_jn function,  \f$ j_{n}(x)= \sqrt{\frac\pi{2x}}J_{n+1/2}(x)\f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the sph_bessel_jn function                                 |
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
  //! \f$\displaystyle  j_{n}(x)= \sqrt{\frac\pi{2x}}J_{n+1/2}(x)\f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'+(x^2-n(n+1))y=0\f$ for which \f$ y(0) = 0\f$ if \f$n \ne 0\f$ else \f$1\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::sph_bessel_jn)(n, x)` computes the derivative of the function at `x`.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/sph_bessel_jn.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_jn_, sph_bessel_jn);
}

#include <eve/module/bessel/regular/impl/sph_bessel_jn.hpp>
