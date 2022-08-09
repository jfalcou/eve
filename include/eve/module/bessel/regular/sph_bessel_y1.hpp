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
  //!   @var sph_bessel_y1
  //!   @brief Computes the spherical Bessel function of the second kind,
  //!   \f$ y_{1}(x)= \sqrt{\frac\pi{2x}}Y_{3/2}(x) \f$.
  //!
  //!   It is a solution of \f$ x^{2}y''+2xy'+(x^2-2)y=0\f$ for which \f$ y(0) = -\infty\f$.
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
  //!      T sph_bessel_y1(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$\displaystyle y_{1}(x)=-\frac{\cos x }{x^2}-\frac{\sin x }x\f$
  //!   is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_y1.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_y1_, sph_bessel_y1);
}

#include <eve/module/bessel/regular/impl/sph_bessel_y1.hpp>
