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
#include <eve/module/elliptic/regular/ellint_rf.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
  template<typename Options>
  struct ellint_1_t : elementwise_callable<ellint_1_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_1_t, ellint_1_);
  };


//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_1
//!   @brief Computes the  elliptic integrals of the first kind :
//!   \f$\mathbf{F}(\phi, k) = \int_0^{\phi} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$ and
//!   \f$\mathbf{K}(k) = \int_0^{\pi/2} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$.
//!
//!   Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
//!   values the result of the incomplete function with a \f$\phi\f$ floating point value
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
//!      constexpr T ellint_1(T k) noexcept;                                       //1
//!
//!      template< eve::floating_ordered_value T,  eve::floating_ordered_value U >
//!      constexpr eve::common_value_t<T, U> ellint_1(T phi, U k) noexcept;        //2
//!   }
//!   @endcode
//!
//!    1. complete elliptic integrals of the first kind.
//!    2. incomplete elliptic integrals of the first kind.
//!
//!   **Parameters**
//!
//!     * `phi`:   [floating real Jacobi amplitude](@ref eve::floating_ordered_value).
//!
//!     * `k`:  [floating real elliptic modulus](@ref eve::floating_ordered_value). `k` must verify
//!             \f$k^2\sin^2\phi \le 1\f$ or the result is NaN. In the complete case this means
//!             \f$|k| \le 1\f$.
//!
//!   **Return value**
//!
//!     1. the complete elliptic integral (corresponding to \f$ \phi = \pi/2 \f$) is returned.
//!     2. the incomplete elliptic integral is returned:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_1.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_1 = functor<ellint_1_t>;


  namespace detail
  {

    template<floating_ordered_value T, callable_options O>
    constexpr EVE_FORCEINLINE T
    ellint_1_(EVE_REQUIRES(cpu_), O const& , T x)
    {
      auto xx = eve::abs(x);
      xx      = if_else(xx > one(as(x)), allbits, xx);
      auto a  = one(as(x));
      auto b  = sqrt(oneminus(sqr(xx)));
      auto c  = xx;
      while( eve::any((eve::abs(c) > eps(as(x)))) )
      {
        auto an = average(a, b);
        auto bn = sqrt(a * b);
        c       = average(a, -b);
        a       = an;
        b       = bn;
      }
      return pio_2(as(x)) / b;
    }

    template<floating_ordered_value T, floating_ordered_value U, callable_options O>
    constexpr common_value_t<T, U>
    ellint_1_(EVE_REQUIRES(cpu_), O const&, T phi00, U xx)
    {
      using r_t = common_value_t<T, U>;
      r_t x = r_t(xx);
      r_t phi0 = r_t(phi00);
      x        = eve::abs(x);
      auto phi = abs(phi0);
      // Carlson's algorithm works only for |phi| <= pi/2,
      // use the integrand's periodicity to normalize phi
      //
      T    rphi         = rem(phi, pio_2(as(phi))); // rempio2 ?
      T    m            = nearest((phi - rphi) / pio_2(as(phi)));
      auto oddm         = is_odd(m);
      m                 = inc[oddm](m);
      T s               = if_else(oddm, mone, one(as(x)));
      rphi              = if_else(oddm, pio_2(as(phi)) - rphi, rphi);
      auto [sinp, cosp] = sincos(rphi);
      sinp *= sinp;
      cosp *= cosp;
      auto notdone = sinp * sqr(x) < one(as(phi));

      auto c    = if_else(notdone, rec[pedantic2](sinp), allbits);
      auto r    = s * ellint_rf(cosp * c, c - sqr(x), c);
      auto xis1 = x == one(as(x));
      if( eve::any(xis1) )
      {
        r = if_else(xis1, if_else(phi == pio_2(as(x)), inf(as(x)), asinh(tan(phi0))), r);
      }
      r             = if_else(rphi < smallestposval(as(x)), s * rphi, r);
      auto mgt0     = is_nez(m) && notdone;
      auto greatphi = eps(as(phi)) * phi > one(as(phi)) && notdone;
      if( eve::any((mgt0 || greatphi) && notdone) )
      {
        auto z = ellint_1(x);
        r += m * z;
        r = if_else(greatphi, phi * z / pio_2(as(x)), r);
      }
      return copysign(r, phi);
    }
  }
}
