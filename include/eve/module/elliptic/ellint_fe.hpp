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
#include <eve/module/core.hpp>
#include <eve/module/elliptic/ellint_rf.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct ellint_fe_t : elementwise_callable<ellint_fe_t, Options, modular_option, eccentric_option, threshold_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE
    auto operator()(T a) const noexcept -> decltype(eve::zip(T(), T()))
    { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_value T0, eve::floating_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
    constexpr EVE_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept -> decltype(eve::zip(eve::common_value_t<T0, T1>(), eve::common_value_t<T0, T1>()))
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_fe_t, ellint_fe_);
  };


//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_fe
//!   @brief `elementwise_callable` object computing the elliptic integrals of the first and second kind kind.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto ellint_fe(floating_value auto k)                                   noexcept; // 1
//!      constexpr auto ellint_fe(floating_value auto phi, floating_value auto k)          noexcept; // 2
//!      constexpr auto ellint_fe[modular](floating_value auto phi, floating_value auto alpha)noexcept; // 2
//!      constexpr auto ellint_fe[eccentric](floating_value auto phi, floating_value auto m)  noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `phi`: [floating Jacobi amplitude](@ref eve::floating_value).
//!     * `k`: [floating elliptic modulus](@ref eve::floating_value). `k` must satisfy
//!             \f$k^2\sin^2\phi \le 1\f$ or the result is `NaN`. In the complete case this means
//!             \f$|k| \le 1\f$.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. the complete elliptic integral  of the first and second kind
//!        \f$\mathbf{K}(k) = \int_0^{\pi/2} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$ and
//!         \f$\mathbf{E}(k) = \int_0^{\pi/2} \scriptstyle \sqrt{1-k^2\sin^2 t}\,\mathrm{d}t\f$ is returned.
//!        (corresponding to \f$ \phi = \pi/2 \f$) are returned.
//!      2. the incomplete elliptic integral  of the first kind is returned:
//!        \f$\mathbf{F}(\phi, k) = \int_0^{\phi} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$
//!
//!   @note Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
//!   values the result of the incomplete function with a \f$\phi\f$ floating point value
//!   representing \f$\pi/2\f$ can differ a lot with the result of the complete call.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: ellint_fe](https://en.cppreference.com/w/cpp/numeric/special_functions/ellint_fe)
//!   *  [DLMF: Elliptic Integrals](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld: Elliptic Integral](https://mathworld.wolfram.com/EllipticIntegral.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/ellint_fe.cpp}
//================================================================================================
  inline constexpr auto ellint_fe = functor<ellint_fe_t>;
//================================================================================================
//! @}
//================================================================================================


  namespace detail
  {

    template<floating_value T, callable_options O>
    constexpr EVE_FORCEINLINE auto
    ellint_fe_(EVE_REQUIRES(cpu_), O const& o, T x)
    {
      return eve::zip(ellint_1[o](x), ellint_2[o](x));
    }

    template<floating_value T, callable_options O>
    constexpr auto
    ellint_fe_(EVE_REQUIRES(cpu_), O const& o, T phi0, T x)
    {
      x         = abs(x);
      if      (O::contains(modular))   x = sin(x);
      else if constexpr(O::contains(eccentric)) x = sqrt(x);
      // Carlson's algorithm works only for |phi| <= pi/2,
      // use the integrand's periodicity to normalize phi
      //
      auto phi  = eve::abs(phi0);
      auto rphi = rem(phi, pio_2(as(phi))); // rempio2 ?
      auto m    = nearest((phi - rphi) / pio_2(as(phi)));
      auto oddm = is_odd(m);
      m         = inc[oddm](m);
      T s       = if_else(oddm, mone, one(as(x)));
      rphi      = if_else(oddm, pio_2(as(phi)) - rphi, rphi);

      auto k2           = sqr(x);
      auto [sinp, cosp] = sincos(rphi);
      auto sinp2   = sqr(sinp);
      auto cosp2   = sqr(cosp);
      auto notdone = sinp2 * k2 <= one(as(phi));
      auto c       = if_else(notdone, rec[pedantic](sinp2), allbits);
      auto cm1     = cosp2*c; // c-1
      auto r       = ellint_rf(cm1, c - k2, c);
      auto testz   = is_eqz(k2);
      auto test1   = k2 == one(as(k2));
      auto mgt0 = is_nez(m) && notdone;

      auto r1    = s*r;
      if( eve::any(test1) )
      {
        r1 = if_else(test1, if_else(phi == pio_2(as(x)), inf(as(x)), asinh(tan(phi))), r);
      }
      r1 = if_else(rphi < smallestposval(as(x)), s * rphi, r);
      auto greatphi = eps(as(phi)) * phi > one(as(phi)) && notdone;
      if( eve::any((mgt0 || greatphi) && notdone) )
      {
        auto z = ellint_1(x);
        r1 += m * z;
        r1 = if_else(greatphi, phi * z / pio_2(as(x)), r);
      }
      auto r2     =  s*(oneminus(k2)*(r +  k2*ellint_rd(cm1, c, c - k2)/3)) + k2 * sqrt(cm1 / (c * (c - k2)));
      r2          = if_else(testz, phi, r2);
      r2          = if_else(test1, sinp2, r2);

      if( eve::any(mgt0) )
      {
        auto mm = if_else(test1 || testz, zero, m);
        r2 += mm * ellint_2[o](x);
      }
      r1 = copysign(r1, phi0);
      r2 = copysign(r2, phi0);
      return eve::zip(r1, r2);
    }
  }
}
