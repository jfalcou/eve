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
  //!   @var sph_bessel_j0
  //!   @brief Computes the spherical Bessel function of the first kind,
  //!   \f$ j_{0}(x)= \sqrt{\frac\pi{2x}}J_{1/2}(x) \f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+2xy'+x^2 y=0\f$ for which \f$ y(0) = 1\f$.
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
  //!      T sph_bessel_j0(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$\displaystyle j_{0}(x)=\frac{\sin x }{x}\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/sph_bessel_j0.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_j0_, sph_bessel_j0);
}

#include <eve/module/bessel/regular/impl/sph_bessel_j0.hpp>
