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
  //!   @var cyl_bessel_jn
  //!   @brief Computes \f$ J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
  //!   {\left({x \over 2}\right)}^{2p+n }\f$.
  //!
  //!  It is the solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which
  //!  \f$ y(0) = 0\f$ if \f$n \ne 0\f$ else \f$1\f$.
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
  //!      template< eve::real_value N, eve::floating_real_value T >
  //!      T cyl_bessel_jn(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:   [real value](@ref eve::real_value) order of the function (non necessarily integral)
  //!
  //!     * `x` :  [real floating value](@ref eve::floating_real_value) argument.
  //!
  //!    **Return value**
  //!
  //!    value of \f$\displaystyle J_{n}(x)=\sum_{p=0}^{\infty}{\frac{(-1)^p}{p!\,\Gamma (p+n +1)}}
  //!    {\left({x \over 2}\right)}^{2p+n }\f$
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/cyl_bessel_jn.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_jn_, cyl_bessel_jn);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_jn.hpp>
