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
#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/elliptic/regular/ellint_rd.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct ellint_d_t : elementwise_callable<ellint_d_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_d_t, ellint_d_);
  };


//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_d
//!   @brief Computes the \f$\mbox{D}\f$ elliptic integrals  :
//!        \f$ \mathbf{D}(\phi, k) = \int_0^{\phi} \frac{\sin^2 t}{\sqrt{1-k^2\sin^2 t}}
//!        \scriptstyle\;\mathrm{d}t\f$ and
//!        \f$ \mathbf{D}(k) = \int_0^{\pi/2} \frac{\sin^2 t}{\sqrt{1-k^2\sin^2 t}}
//!        \scriptstyle\;\mathrm{d}t\f$.
//!
//!   Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
//!   values the result of the incomplete  function with a \f$\phi\f$ floating point value
//!   representing \f$\pi/2\f$ can differ a lot with the result of the complete call.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/elliptic.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_ordered_value T >
//!      constexpr T ellint_d(T k) noexcept;                                       //1
//!
//!      template< eve::floating_ordered_value T, eve::floating_ordered_value U >
//!      constexpr eve::common_value_t<T, U> ellint_d(T phi, U k) noexcept;        //2
//!   }
//!   @endcode
//!
//!    1. complete \f$\mbox{D}\f$  elliptic integrals.
//!    2. incomplete\f$\mbox{D}\f$ elliptic integrals.
//!
//!
//!   **Parameters**
//!
//!     * `phi`: [floating real Jacobi amplitude](@ref eve::floating_ordered_value).
//!
//!     * `k`:  [floating real elliptic modulus](@ref eve::floating_ordered_value).
//!             `k` must verify \f$k^2\sin^2\phi \le 1\f$ or the result is NaN. In the complete case,
//!             this means \f$|k| \le 1\f$.
//!
//!   **Return value**
//!
//!     1. the complete elliptic integral ( corresponding to \f$ \phi = \pi/2 \f$ ) is returned.
//!     2. the incomplete elliptic integral of the first kind is returned:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_d.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_d = functor<ellint_d_t>;

  namespace detail
  {

    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T
    ellint_d_(EVE_REQUIRES(cpu_), O const& , T k) noexcept
    {
      auto r       = nan(as(k));
      auto t       = sqr(k);
      auto notdone = t < one(as(t));
      auto x(zero(as(k)));
      auto y = oneminus(t);
      auto z(one(as(k)));
      return if_else(notdone, if_else(t < eps(as(k)), pio_4(as(k)), ellint_rd(x, y, z) / 3), r);
    }

    template<typename T, typename U, callable_options O>
    constexpr T
    ellint_d_(EVE_REQUIRES(cpu_), O const&, T phi00, U kk) noexcept
    {
      using r_t = common_value_t<T, U>;
      r_t k = r_t(kk);
      r_t phi0 = r_t(phi00);
      auto aphi    = eve::abs(phi0);
      auto r       = nan(as(aphi));
      auto notdone = is_finite(aphi);
      r            = if_else(notdone, r, inf(as(phi0)));
      if( eve::any(notdone) )
      {
        auto br_philarge = [aphi](auto k) // aphi*eps(as(aphi)) > one(as(aphi))
          { return aphi * ellint_d(k) / pio_2(as(aphi)); };
        notdone = next_interval(br_philarge, notdone, aphi * eps(as(aphi)) > one(as(aphi)), r, k);
        if( eve::any(notdone) )
        {
          auto rphi         = rem(aphi, pio_2(as(aphi)));
          auto m            = nearest((aphi - rphi) / pio_2(as(aphi)));
          auto oddm         = is_odd(m);
          m                 = inc[oddm](m);
          T s               = if_else(oddm, mone, one(as(k)));
          rphi              = if_else(oddm, pio_2(as(phi0)) - rphi, rphi);
          auto [sinp, cosp] = sincos(rphi);
          T    c            = rec[pedantic2](sqr(sinp));
          T    cm1          = sqr(cosp) * c; // c - 1
          T    k2           = sqr(k);
          auto br_reg       = [c, cm1, k2, s, m](auto k){
            auto z    = if_else(is_finite(c), s * ellint_rd(cm1, c - k2, c) / 3, zero);
            auto test = is_nez(m);
            if( eve::any(test) ) { return z + m * ellint_d(k); }
            else return z;
          };
          notdone = last_interval(br_reg, notdone, r, k);

          r = if_else(k2 * sinp * sinp > one(as(phi0)), allbits, r);
          r = if_else(is_eqz(phi0), zero, r);
        }
      }
      return copysign(r, phi0);
    }
  }
}
