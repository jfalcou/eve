//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct cyl_bessel_kn_t : elementwise_callable<cyl_bessel_kn_t, Options>
  {
    template<eve::ordered_value N, eve::floating_ordered_value T>
     as_wide_as_t<T, N> operator()(N n, T x) const  { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(cyl_bessel_kn_t, cyl_bessel_kn_);
  };

  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var cyl_bessel_kn
  //!   @brief Computes the modified Bessel function of the second kind,
  //!    \f$ K_n(x)=\frac{\Gamma(n+1/2)(2x)^n}{\sqrt\pi} \int_{0}^{\infty}\frac{\cos\tau}
  //!   {(\tau^2+x^2)^{n+1/2}}\,\mathrm{d}\tau\f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+xy'-(x^2+n^2)y=0\f$ for which \f$ y(0) = \infty\f$.
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
  //!      T cyl_bessel_kn(N n, T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `n`:   order of the function (non necessarily integral)
  //!
  //!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$\displaystyle K_n(x)=\frac{\Gamma(n+1/2)(2x)^n}{\sqrt\pi}
  //!   \int_{0}^{\infty}\frac{\cos\tau}{(\tau^2+x^2)^{n+1/2}}\,\mathrm{d}\tau\f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_kn.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto cyl_bessel_kn = functor<cyl_bessel_kn_t>;
}

#include <eve/module/bessel/regular/impl/cyl_bessel_kn.hpp>
