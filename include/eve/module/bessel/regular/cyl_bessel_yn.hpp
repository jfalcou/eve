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
  //!   @var cyl_bessel_yn
  //!   @brief Computes the Bessel functions of the second kind,
  //!   \f$ Y_{n}(x)=\frac{2(z/2)^{-n}}{\sqrt\pi\, \Gamma(1/2-n)}\int _{1}^{\infty}\frac{\cos x\tau}
  //!   {(\tau^2-1)^{n+1/2}}\,\mathrm {d} \tau \f$.
  //!
  //!   It is a solution of \f$ x^{2}y''+xy'+(x^2-n^2)y=0\f$ for which \f$ y(0) = \infty\f$.
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
  //!      template< eve::ordered_value N, eve::floating_ordered_value T >
  //!      T cyl_bessel_yn(N n, T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:   [ordered value](@ref eve::ordered_value) order of the function.
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!   **Return value**
  //!
  //!   The value of  \f$\displaystyle Y_{n}(x)=\frac{2(z/2)^{-n}}{\sqrt\pi\,
  //!   \Gamma(1/2-n)}\int _{1}^{\infty}\frac{\cos x\tau}{(\tau^2-1)^{n+1/2}}\,\mathrm {d} \tau \f$
  //!   is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_yn.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_yn_, cyl_bessel_yn);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_yn.hpp>
