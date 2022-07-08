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
  //!   @var sph_bessel_yn
  //!   @brief Computes the \f$ y_{n}(x)= \sqrt{\frac\pi{2x}}Y_{n+1/2}(x)\f$.
  //!
  //!  It is a solution of \f$ x^{2}y''+2xy'+(x^2-n(n+1))y=0\f$ for which \f$ y(0) = -\infty\f$
  //!
  //!   **Alternative Header**
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
  //!      T sph_bessel_yn(N n, T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:   [real value](@ref eve::real_value) order of the function (integral and positive),
  //!
  //!     * `x` :  [real floating value](@ref eve::floating_real_value) argument.
  //!
  //!    **Return value**
  //!
  //!    value of \f$ \displaystyle y_{n}(x)=
  //!    (-x)^n\left(\frac1x\frac{d}{dx}\right)^n \frac{\cos x}x\f$
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/sph_bessel_yn.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_yn_, sph_bessel_yn);
}

#include <eve/module/bessel/regular/impl/sph_bessel_yn.hpp>
