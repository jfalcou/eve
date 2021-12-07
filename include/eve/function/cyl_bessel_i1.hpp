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
  //! @var cyl_bessel_i1
  //!
  //! @brief Callable object computing \f$ I_1(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\cos\tau\,\mathrm{d}\tau\f$.
  //!
  //! **Required header:** `#include <eve/function/cyl_bessel_i1.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the cyl_bessel_i1 function                                 |
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
  //! \f$ \displaystyle I_1(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\cos\tau\,\mathrm{d}\tau\f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'-(1+x^2)y=0\f$ for which \f$ y(0) = 0\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/cyl_bessel_i1.hpp>`
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_i1)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/cyl_bessel_i1.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_i1_, cyl_bessel_i1);
}

#include <eve/module/real/special/function/regular/generic/cyl_bessel_i1.hpp>
