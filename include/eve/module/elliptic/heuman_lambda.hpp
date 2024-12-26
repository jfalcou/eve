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
  struct heuman_lambda_t : elementwise_callable<heuman_lambda_t, Options>
  {

    template<eve::floating_value T0, eve::floating_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
      constexpr EVE_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(heuman_lambda_t, heuman_lambda_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var heuman_lambda
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
//!      constexpr auto heuman_lambda(floating_value auto u, floating_value auto x)                  noexcept; // 1
//!
//!      //Semantic modifiers
//!      constexpr auto heuman_lambda[modular](floating_value auto u, floating_value auto alpha)     noexcept; // 1
//!      constexpr auto heuman_lambda[eccentric(floating_value auto u, floating_value auto k)        noexcept; // 1
//!      constexpr auto heuman_lambda[threshold = tol](floating_value auto u, floating_value auto x) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto heuman_lambda[conditional_expr auto c](/*any of the above overloads*/)       noexcept; // 2
//!      constexpr auto heuman_lambda[logical_value autolm](/*any of the above overloads*/)          noexcept; // 2
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
//!   *  [Wikipedia: Jacobi elliptic functions](https://en.wikipedia.org/wiki/heuman_lambda_functions)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/heuman_lambda.cpp}
//================================================================================================
  inline constexpr auto heuman_lambda = functor<heuman_lambda_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<floating_value T, callable_options O>
    auto heuman_lambda_(EVE_REQUIRES(cpu_), O const&, T phi, T k) noexcept
    {
      auto test = eve::abs(phi) <= pio_2(as(k));
      auto k2 = sqr(k);
      auto kp = oneminus(k2);
      T r1(zero(as(k))), r2(zero(as(k)));
      if (eve::any(test))
      {
        auto [sinp, cosp] = sincos(phi);
        auto s2 = sqr(sinp);
        auto delta = sqrt(oneminus(kp*s2));
        r1 = kp * sinp * cosp / (delta * pio_2(as(k)));
        auto invsqrdelta = rec(sqr(delta));
        auto z1 =  ellint_rf(T(0), kp, T(1));
        auto z2 =  ellint_rj(zero(as(k)), kp, one(as(k)), oneminus(k2*invsqrdelta))*invsqrdelta/3;
        r1 *= fma(k2, z2, z1);
      }
      if (eve::any(!test))
      {
        auto rkp = sqrt(kp);
        auto  ratio = ellint_1(phi, rkp) / ellint_1(rkp);
        r2 = if_else(rkp == one(as(rkp)), inf(as(rkp)), ratio + ellint_1(k) * jacobi_zeta(phi, rkp) / pio_2(as(k)));
      }
      auto r = if_else(k2 > one(as(k2)), allbits, if_else(test, r1, r2));
      return if_else(phi == pio_2(as(phi)), one, r); //this is a guess about what user wants as pio_2 is not exact
    }
  }
}
