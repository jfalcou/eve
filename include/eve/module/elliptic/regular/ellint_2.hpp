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
#include <eve/module/elliptic/regular/ellint_rd.hpp>
#include <eve/module/elliptic/regular/ellint_rf.hpp>
#include <eve/module/elliptic/regular/ellint_rg.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct ellint_2_t : elementwise_callable<ellint_2_t, Options>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_value T0, eve::floating_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_2_t, ellint_2_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_2
//!   @brief `elementwise_callable` object computing the  elliptic integrals of the second kind.
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
//!      constexpr auto ellint_2(floating_value auto k)                                   noexcept; // 1
//!      constexpr auto ellint_2(floating_value auto phi, floating_value auto k)          noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto ellint_2[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 3
//!      constexpr auto ellint_2[logical_value auto m](/*any of the above overloads*/)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `phi`: [floating Jacobi amplitude](@reffloating_value).
//!     * `k`: [floating elliptic modulus](@ref floating_value). `k` must satisfy
//!             \f$k^2\sin^2\phi \le 1\f$ or the result is `NaN`. In the complete case this means
//!             \f$|k| \le 1\f$.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!      1. the complete ( corresponding to \f$ \phi = \pi/2 \f$ )of the second kind:
//!         \f$\mathbf{E}(k) = \int_0^{\pi/2} \scriptstyle \sqrt{1-k^2\sin^2 t}\,\mathrm{d}t\f$ is returned.
//!      2. the incomplete elliptic integrals of the second kind:
//!        \f$ \mathbf{E}(\phi, k) = \int_0^{\phi} \scriptstyle \sqrt{1-k^2\sin^2 t}\,\mathrm{d}t\f$ is returned.
//!      3. [The operation is performed conditionnaly](@ref conditional)
//!
//!   @note Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
//!   values the result of the incomplete  function with a \f$\phi\f$ floating point value
//!   representing \f$\pi/2\f$ can differ a lot with the result of the complete call.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/ellint_2)
//!   *  [DLMF](https://dlmf.nist.gov/19.2)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/EllipticIntegral.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/ellint_2.cpp}
//================================================================================================
  inline constexpr auto ellint_2 = functor<ellint_2_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T
    ellint_2_(EVE_REQUIRES(cpu_), O const&, T k)
    {
      auto k2 = sqr(k);
      auto r  = 2 * ellint_rg(zero(as(k)), oneminus(k2), one(as(k)));
      return if_else(k2 == one(as(k)), one, r);
    }

    template<typename T, typename U, callable_options O>
    constexpr common_value_t<T, U>
    ellint_2_(EVE_REQUIRES(cpu_), O const&, T phi00, U xx)
    {
      using r_t = common_value_t<T, U>;
      r_t x = r_t(xx);
      r_t phi0 = r_t(phi00);
      x        = eve::abs(x);
      auto phi = abs(phi0);
      // Carlson's algorithm works only for |phi| <= pi/2,
      // use the integrand's periodicity to normalize phi
      //
      T    rphi = rem(phi, pio_2(as(phi))); // rempio2 ?
      T    m    = nearest((phi - rphi) / pio_2(as(phi)));
      auto oddm = is_odd(m);
      m         = inc[oddm](m);
      T s       = if_else(oddm, mone, one(as(x)));
      rphi      = if_else(oddm, pio_2(as(phi)) - rphi, rphi);

      auto k2           = sqr(x);
      auto [sinp, cosp] = sincos(rphi);
      auto sinp2        = sqr(sinp);
      auto notdone      = sinp2 * k2 <= one(as(phi));
      auto c            = if_else(notdone, rec[pedantic](sinp2), allbits);
      auto cm1          = sqr(cosp) * c; // c-1
      auto r =
        s
        * (oneminus(k2) * ellint_rf(cm1, c - k2, c)
           + k2 * (oneminus(k2)) * ellint_rd(cm1, c, c - k2) / 3 + k2 * sqrt(cm1 / (c * (c - k2))));
      auto testz = is_eqz(k2);
      auto test1 = k2 == one(as(k2));

      r         = if_else(testz, phi, r);
      r         = if_else(test1, sinp, r);
      auto mgt0 = is_nez(m) && notdone;
      if( eve::any(mgt0) )
      {
        m = if_else(test1 || testz, zero, m);
        r += m * ellint_2(x);
      }
      return copysign(r, phi);
    }
  }
}
