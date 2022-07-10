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
  //!   @var airy_bi
  //!   @brief Computes the airy function \f$ Bi(x)\f$.
  //!
  //!  It is the solution of the differential equation \f$y''-xy = 0\f$ satisfying
  //!  \f$Ai(0) = \frac1{3^{1/6}\Gamma(2/3)}\f$ and
  //!  \f$Ai'(0) =\frac{3^{1/6}}{\Gamma(1/3)}\f$.
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
  //!      T airy_bi(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!    **Return value**
  //!
  //!     The value of \f$ \displaystyle Bi(x) = \frac1{\pi}\int_{0}^{\infty}
  //!     \left[\exp\left(-{\frac{t^{3}}{3}}+xt\right)+
  //!     \sin\left({\frac{t^{3}}{3}}+xt\right)\,\right]dt\f$
  //!     is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/bessel/regular/airy_bi.cpp}
  //! @}
  //================================================================================================

  EVE_MAKE_CALLABLE(airy_bi_, airy_bi);
}

#include <eve/module/bessel/regular/impl/airy_bi.hpp>
