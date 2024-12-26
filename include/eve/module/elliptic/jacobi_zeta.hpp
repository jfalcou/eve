//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/module/elliptic/ellint_rf.hpp>
#include <eve/module/elliptic/ellint_rj.hpp>
#include <eve/module/elliptic/ellint_1.hpp>
#include <eve/module/elliptic/jacobi_zeta.hpp>

namespace eve
{
  template<typename Options>
  struct jacobi_zeta_t : elementwise_callable<jacobi_zeta_t, Options>
  {

    template<eve::floating_value T0, eve::floating_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
      constexpr EVE_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(jacobi_zeta_t, jacobi_zeta_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var jacobi_zeta
//!   @brief `elementwise_callable` object computing the  Jacobi's sn, cn and dn function simultaneously.
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
//!      constexpr auto jacobi_zeta(floating_value auto u, floating_value auto x)                  noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto jacobi_zeta[conditional_expr auto c](/*any of the above overloads*/)       noexcept; // 2
//!      constexpr auto jacobi_zeta[logical_value autolm](/*any of the above overloads*/)          noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `u`: argument.
//!     * `m`: amplitude parameter (\f$0\le m\le 1).
//!     * `alpha `: modular angle in radian.
//!     * `tol': accuracy tolerance (by defaut [epsilon](@ref eve::epsilon).
//!     * `k`: elliptic modulus (eccentricity) .
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `l`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. return a `kumi::tuple` containing `sn``cn` and `dn` values. Take care that the meaning of the second parameters
//!         depends on the option used (see note below).
//!      2. [The operation is performed conditionally](@ref conditional)
//!
//! @note
//!   * \f$\alpha\f$ is named the modular angle given in radian (modular option).
//!   * \f$ k = \sin\alpha \f$ is named the elliptic modulus or eccentricity (eccentric option).
//!   * \f$ m = k^2 = \sin^2\alpha\f$ is named the parameter (no option).
//!   Each of the above three quantities is completely determined by any of the others (given that they are non-negative).
//!   Thus, they can be used interchangeably (give the right option).

//!  @groupheader{External references}
//!   *  [DLMF: Jacobian Elliptic](https://dlmf.nist.gov/22.2)
//!   *  [Wolfram MathWorld: Jacobi Elliptic Functions](https://mathworld.wolfram.com/JacobiEllipticFunctions.html)
//!   *  [Wikipedia: Jacobi elliptic functions](https://en.wikipedia.org/wiki/jacobi_zeta_functions)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/jacobi_zeta.cpp}
//================================================================================================
  inline constexpr auto jacobi_zeta = functor<jacobi_zeta_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<floating_value T, callable_options O>
    auto jacobi_zeta_(EVE_REQUIRES(cpu_), O const&, T phi, T k) noexcept
    {
      auto aphi = eve::abs(phi);
      auto [sinp, cosp] = sincos(aphi);
      auto s2 = sqr(sinp);
      auto k2 = sqr(k);
      auto kp = oneminus(k2);
      auto k2s2c = oneminus(k2*s2);
      auto e_rj = ellint_rj(zero(as(phi)), kp, one(as(phi)), k2s2c);
      auto e_1 = ellint_1(k);
      auto r = if_else(k2 == one(as(k)),  eve::signnz(cosp)*sinp
                      , k2*sinp*cosp*sqrt(k2s2c)*e_rj/(3*e_1));
      r =  if_else(aphi == pio_2(as(phi)), zero, r); //this is a guess of what the user wants pio_2 being not exact
      return negate(r, phi); ;
    }
  }
}
