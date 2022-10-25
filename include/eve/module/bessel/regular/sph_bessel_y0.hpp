//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var sph_bessel_y0
  //!   @brief Computes the spherical Bessel function of the second kind,
  //!   \f$ y_{0}(x)= \sqrt{\frac\pi{2x}}Y_{1/2}(x) \f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+2xy'+x^2 y=0\f$ for which \f$ y(0) = -\infty\f$.
  //!
  //!   **Defined in header**
  //!
  //!   @code
  //!   #include <eve/module/bessel.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_real_value T >
  //!      T sph_bessel_y0(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real_value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$\displaystyle y_{0}(x)=-\frac{\cos x }{x}\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_y0.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_y0_, sph_bessel_y0);
}

#include <eve/module/bessel/regular/impl/sph_bessel_y0.hpp>
