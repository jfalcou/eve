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
  //!   @var cyl_bessel_y1
  //!   @brief Computes the Bessel function of the second kind,
  //!    \f$ Y_1(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
  //!   {(\tau^2-1)^{3/2}}\,\mathrm{d}\tau\f$.
  //!
  //!   It is a solution of \f$ x^{2}y''+xy'+(x^2-1)y=0\f$ for which \f$ y(0) = \infty\f$.
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
  //!      template< eve::floating_ordered_value T >
  //!      T cyl_bessel_y1(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$\displaystyle Y_1(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
  //!   {(\tau^2-1)^{3/2}}\,\mathrm{d}\tau\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_y1.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_y1_, cyl_bessel_y1);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_y1.hpp>
