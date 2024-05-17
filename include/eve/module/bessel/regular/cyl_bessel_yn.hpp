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
  struct cyl_bessel_yn_t : strict_elementwise_callable<cyl_bessel_yn_t, Options>
  {
    template<eve::value N, eve::floating_value T>
    EVE_FORCEINLINE constexpr
    as_wide_as_t<T, N> operator()(N n, T x) const noexcept
      requires (same_lanes_or_scalar<N, T>)
    { return EVE_DISPATCH_CALL(n, x); }

    EVE_CALLABLE_OBJECT(cyl_bessel_yn_t, cyl_bessel_yn_);
  };

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
  //!     template< eve::value N, eve::floating_value T >
  //!     constexpr T cyl_bessel_yn(N n, T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `n`: Order of the function.
  //!   * `x`: [Floating argument](@ref eve::floating_value).
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
 inline constexpr auto cyl_bessel_yn = functor<cyl_bessel_yn_t>;
}

#include <eve/module/bessel/regular/impl/cyl_bessel_yn.hpp>
