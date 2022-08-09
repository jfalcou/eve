//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
  //!   @var cyl_bessel_k1
  //!   @brief Computes the modified Bessel function of the second kind,
  //!   \f$ K_1(x)=\int_{0}^{\infty} e^{-x \cosh \tau} \cosh \tau\,\mathrm{d}\tau\f$.
  //!
  //!   It is a solution of \f$ x^{2}y''+xy'-(1+x^2)y=0\f$ for which \f$ y(0) = \infty\f$.
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
  //!      T cyl_bessel_k1(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  positive [real floating argument](@ref eve::floating_real__value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$ \displaystyle K_1(x)=\int_{0}^{\infty} e^{-x \cosh \tau}
  //!   \cosh \tau\,\mathrm{d}\tau\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_k1.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_k1_, cyl_bessel_k1);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_k1.hpp>
