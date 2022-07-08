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
  //!   @var sph_bessel_jn
  //!   @brief Computes the spherical Bessel functions of the first kind,
  //!   \f$ j_{n}(x)= \sqrt{\frac\pi{2x}}J_{n+1/2}(x)\f$.
  //!
  //!  It is the solution of \f$ x^{2}y''+2xy'+(x^2-n(n+1))y=0\f$ for which \f$ y(0) = 0\f$ if \f$n \ne 0\f$ else \f$1\f$.
  //!
  //!   **Defined in Header**
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
  //!      template< eve::integral_real_value N, eve::floating_real_value T >
  //!      T sph_bessel_jn(N n, T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:   order of the function. Order must be positive,
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!    **Return value**
  //!
  //!    the value of \f$ \displaystyle j_{n}(x)=
  //!    (-x)^n\left(\frac1x\frac{d}{dx}\right)^n \frac{\sin x}x\f$
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/sph_bessel_jn.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_jn_, sph_bessel_jn);
}

#include <eve/module/bessel/regular/impl/sph_bessel_jn.hpp>
