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
  //! @var sph_bessel_y1
  //!
  //! @brief Callable object computing \f$ y_{1}(x)= \sqrt{\frac\pi{2x}}Y_{3/2}(x) \f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the sph_bessel_y1 function   |
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
  //! \f$ Y_0(x)=\frac1{\pi }\int _{0}^{\pi}\cos(x\sin \tau )\,\mathrm {d} \tau \f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::sph_bessel_y1)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/sph_bessel_y1.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_y1_, sph_bessel_y1);
}

#include <eve/module/bessel/regular/impl/sph_bessel_y1.hpp>
