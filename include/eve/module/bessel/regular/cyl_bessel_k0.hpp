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
  //! @var cyl_bessel_k0
  //!
  //! @brief Callable object computing  \f$ K_0(x)=\int_{0}^{\infty}\frac{\cos(x\tau)}{\sqrt{\tau^2+1}}\,\mathrm{d}\tau\f$.
  //!
  //! **Required header:** `#include <eve/function/cyl_bessel_k0.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the modified cyl_bessel_k0 function of the second kind     |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< floating_real_value T > auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:  positive  [floating_real_value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Computes  [elementwise](@ref glossary_elementwise) the value of
  //!  \f$ \displaystyle K_0(x)=\int_{0}^{\infty}\frac{\cos(x\tau)}{\sqrt{\tau^2+1}}\,\mathrm{d}\tau\f$.
  //!
  //! It is a solution of \f$ x^{2}y''+xy'-x^2y=0\f$ for which \f$ y(0) = \infty\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/cyl_bessel_k0.hpp>`
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_k0)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/cyl_bessel_k0.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_k0_, cyl_bessel_k0);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_k0.hpp>
