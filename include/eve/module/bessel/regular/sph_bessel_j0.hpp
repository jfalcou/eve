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
  //!   @var sph_bessel_j0
  //!   @brief Computes  \f$ j_{0}(x)= \sqrt{\frac\pi{2x}}J_{1/2}(x) \f$.
  //!
  //!  It is the solution of \f$ x^{2}y''+2xy'+x^2 y=0\f$ for which \f$ y(0) = 1\f$.
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
  //!      T sph_bessel_j0(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating value](@ref eve::floating_real_value) argument.
  //!
  //!    **Return value**
  //!
  //!    value of \f$\displaystyle j_{0}(x)=\frac{\sin x }{x}\f$
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/sph_bessel_j0.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(sph_bessel_j0_, sph_bessel_j0);
}

#include <eve/module/bessel/regular/impl/sph_bessel_j0.hpp>
