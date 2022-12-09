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
  //!   @var airy_ai
  //!   @brief Computes the airy function \f$ Ai(x)\f$.
  //!
  //!   It is the solution of the differential equation \f$y''-xy = 0\f$ satisfying
  //!   \f$Ai(0) = \frac1{3^{2/3}\Gamma(2/3)}\f$ and \f$Ai'(0) =\frac1{3^{1/3}\Gamma(1/3)}\f$.
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
  //!      T airy_ai(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!    **Return value**
  //!
  //!    The value of \f$ \displaystyle Ai(x)=\frac1{\pi} \int_{0}^{\infty}\cos
  //!    \left( \frac{t^3}{3}+xt \right) \,dt\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/airy_ai.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(airy_ai_, airy_ai);
}

#include <eve/module/bessel/regular/impl/airy_ai.hpp>
