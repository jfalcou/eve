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
  //!   @var sph_bessel_j1
  //!   @brief Computes the spherical Bessel function of the first kind,
  //!   \f$ j_{1}(x)= \sqrt{\frac\pi{2x}}J_{3/2}(x) \f$.
  //!
  //!   It is the  solution of \f$ x^{2}y''+2xy'+(x^2-2)y=0\f$ for which \f$ y(0) = 0\f$
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
  //!      T sph_bessel_j1(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$ \displaystyle j_{1}(x)= \frac{\sin x}{x^2}- \frac{\cos x}{x}\f$
  //!   is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_j1.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_j1_, sph_bessel_j1);
}

#include <eve/module/bessel/regular/impl/sph_bessel_j1.hpp>
