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
  //! @var cyl_bessel_j1
  //!
  //! @brief Callable object computing \f$ J_1(x)=\frac1{\pi }\int _{0}^{\pi}\cos(\tau-x\sin \tau )\,\mathrm {d} \tau \f$.
  //!
  //! **Required header:** `#include <eve/function/cyl_bessel_j1.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the cyl_bessel_j1 function   |
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
  //! \f$ J_1(x)=\frac1{\pi }\int _{0}^{\pi}\cos(\tau-x\sin \tau )\,\mathrm {d} \tau \f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'+(x^2-1)y=0\f$ for which \f$ y(0) = 0\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/cyl_bessel_j1.hpp>`
  //!
  //!     The expression `eve::diff(eve::cyl_bessel_j1)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/cyl_bessel_j1.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_j1_, cyl_bessel_j1);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_j1.hpp>
