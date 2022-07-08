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
  //!   @var cyl_bessel_i0
  //!   @brief Computes  \f$ I_0(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\,\mathrm{d}\tau\f$.
  //!
  //! It is the solution of \f$ x^{2}y''+xy'-x^2y=0\f$ for which \f$ y(0) = 0\f$.
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
  //!      template< eve::floating_real_value T >
  //!      T cyl_bessel_i0(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :   positive [real floating value](@ref eve::floating_real_value) argument.
  //!
  //!    **Return value**
  //!
  //!    value of \f$ \displaystyle I_0(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\,\mathrm{d}\tau\f$
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/cyl_bessel_i0.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_i0_, cyl_bessel_i0);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_i0.hpp>
