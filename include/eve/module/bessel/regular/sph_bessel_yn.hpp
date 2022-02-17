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
  //! @var sph_bessel_yn
  //!
  //! @brief Callable object computing the sph_bessel_yn function,  \f$ y_{n}(x)= \sqrt{\frac\pi{2x}}Y_{n+1/2}(x)\f$.
  //!
  //! **Required header:** `#include <eve/module/bessel.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the sph_bessel_yn function                                 |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value N, floating_real_value T  > auto operator()( N n, T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`n`:   [real_value](@ref eve::real_value) order of the function (integral and positive)
  //!
  //!`x`:   [floating_real_value](@ref eve::floating_real_value) (positive).
  //!
  //! **Return value**
  //!
  //! \f$\displaystyle  y_{n}(x)= \sqrt{\frac\pi{2x}}Y_{n+1/2}(x)\f$.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_nth
  //!
  //!
  //!     The expression `eve::diff(eve::sph_bessel_yn)(n, x)` computes the derivative of the function at `x`.
  //!
  //!
  //! #### Example
  //!
  //! @godbolt{doc/bessel/sph_bessel_yn.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_yn_, sph_bessel_yn);
}

#include <eve/module/bessel/regular/impl/sph_bessel_yn.hpp>
