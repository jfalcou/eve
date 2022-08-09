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
  //!   @var cyl_bessel_k0
  //!   @brief Computes the modified Bessel function of the second kind,
  //!   \f$ K_0(x)=\int_{0}^{\infty}\frac{\cos(x\tau)}
  //!   {\sqrt{\tau^2+1}}\,\mathrm{d}\tau\f$.
  //!
  //!   It is a solution \f$ x^{2}y''+xy'-x^2y=0\f$ for which \f$ y(0) = \infty\f$.
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
  //!      T cyl_bessel_k0(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$ \displaystyle K_0(x)=\int_{0}^{\infty}\frac{\cos(x\tau)}
  //!   {\sqrt{\tau^2+1}}\,\mathrm{d}\tau\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_k0.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_k0_, cyl_bessel_k0);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_k0.hpp>
