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
  //!   @var cyl_bessel_y0
  //!   @brief Computes the Bessel function of the second kind,
  //!   \f$ Y_0(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
  //!   {\sqrt{\tau^2-1}}\,\mathrm {d} \tau\f$.
  //!
  //!  It is a solution of \f$ x^{2}y''+xy'+x^2y=0\f$ for which \f$ y(0) = \infty\f$.
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
  //!      template< eve::floating_real_value T >
  //!      T cyl_bessel_y0(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!    **Return value**
  //!
  //!    the value of \f$\displaystyle Y_0(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
  //!    {\sqrt{\tau^2-1}}\,\mathrm {d} \tau\f$
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/regular/cyl_bessel_y0.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_y0_, cyl_bessel_y0);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_y0.hpp>
