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
  //! @var sph_bessel_j0
  //!
  //! @brief Callable object computing \f$ j_{0}(x)= \sqrt{\frac\pi{2x}}J_{1/2}(x) \f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the sph_bessel_j0 function   |
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
  //!the solution of \f$ x^{2}y''+xy'+(x^2-1/2)y=0\f$ for which \f$ y(0) = 1\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::sph_bessel_j0)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/sph_bessel_j0.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_j0_, sph_bessel_j0);
}

#include <eve/module/bessel/regular/impl/sph_bessel_j0.hpp>
