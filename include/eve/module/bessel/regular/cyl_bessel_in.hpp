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
  //!   @var cyl_bessel_in
  //!   @brief Computes  the modified Bessel functions of the first kind,
  //!    \f$ I_{n}(x)=\left(\frac12z\right)^n\sum_{k=0}^{\infty}{\frac{(x^2/4)^k}{k!\,\Gamma (k+n +1)}}\f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which \f$ y(0) = 0\f$.
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
  //!      template< eve::real_value N, eve::floating_real_value T >
  //!      T cyl_bessel_in(N n, T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:  order of the function (non necessarily integral),
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!    **Return value**
  //!
  //!    the value of \f$\displaystyle I_{n}(x)=\left(\frac12z\right)^n\sum_{k=0}^{\infty}{\frac{(x^2/4)^k}{k!\,\Gamma (k+n +1)}}\f$
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/regular/cyl_bessel_in.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_in_, cyl_bessel_in);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_in.hpp>
