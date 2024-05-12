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
  //!   @var cyl_bessel_i1
  //!   @brief Computes  the modified Bessel function of the first kind,
  //!   \f$ I_1(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}\cos\tau\,\mathrm{d}\tau\f$.
  //!
  //!   It is the solution of  \f$ x^{2}y''+xy'-(1+x^2)y=0\f$ for which \f$ y(0) = 0\f$.
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
  //!      T cyl_bessel_i1(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!   **Return value**
  //!
  //!   The value of  \f$ \displaystyle I_1(x)=\frac1{\pi}\int_{0}^{\pi}e^{x\cos\tau}
  //!   \cos\tau\,\mathrm{d}\tau\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_i1.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_i1_, cyl_bessel_i1);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_i1.hpp>
