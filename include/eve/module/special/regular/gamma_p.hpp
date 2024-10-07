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
#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve
{
template<typename Options>
struct gamma_p_t : elementwise_callable<gamma_p_t, Options>
{
  template<floating_value T0, floating_value T1>
  EVE_FORCEINLINE common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept
    requires (same_lanes_or_scalar<T0, T1>)
  {
    return EVE_DISPATCH_CALL_PT((common_value_t<T0, T1>), a, b);
  }

  EVE_CALLABLE_OBJECT(gamma_p_t, gamma_p_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var gamma_p
//!   @brief `elementwise_callable` object computing the normalized lower incomplete \f$\Gamma\f$ function.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto gamma_p(floating_value auto x, floating_value auto y)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto gamma_p[conditional_expr auto c](floating_value auto x, floating_value auto y) noexcept; // 2
//!      constexpr auto gamma_p[logical_value auto m](floating_value auto x, floating_value auto y)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of the normalized lower incomplete \f$\Gamma\f$ function:
//!        \f$\displaystyle \frac{1}{\Gamma(x)}\int_0^{y} t^{x-1}e^{-t}\mbox{d}t\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wikipedia: Incomplete gamma function](https://en.wikipedia.org/wiki/Incomplete_gamma_function)
//!   *  [DLMF](https://dlmf.nist.gov/8.2)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/gamma_p.cpp}
//================================================================================================
  inline constexpr auto gamma_p = functor<gamma_p_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<callable_options O, typename T>
    constexpr auto
    gamma_p_(EVE_REQUIRES(cpu_), O const&, T x, T a) noexcept
    {
      auto const third   = T(1 / 3.0);
      auto       res     = nan(as<T>()); // nan case treated here
      auto       notdone = is_not_nan(x);
      const auto amax    = T(1048576);
      auto       test    = (a > amax);
      if( eve::any(test) )
      {
        auto z = eve::fma(1024 * rsqrt(a), x - (a - third), amax - third);
        x      = eve::max(z, zero(as(x)));
        a      = if_else(test, amax, a);
      }
      auto lginc = [](auto a0, auto a1, auto tt){
        // insure convergence in each case for all members of simd vector
        // making x = a+1 when the tt do not succeed
        auto lx = if_else(tt, a0, a1);

        // Series expansion for x < a+1
        auto ap  = a1;
        auto del = one(as(ap));
        auto ss = del;

        while( eve::any(abs(del) >= T(100) * epsilon(maximum(abs(ss)))) )
        {
          ap += one(as(ap));
          del = lx * del / ap;
          ss += del;
        }
        auto b = ss * eve::exp(fms(a1, eve::log(lx), eve::log_abs_gamma(inc(a1)) + lx));
        //  For very small a, the series may overshoot very slightly.
        b = eve::min(b, one(as(b)));
        //  if lower, b(k) = bk; else b(k) = 1-bk; end
        return if_else(is_eqz(a0) && is_eqz(a1), one, b);
      };
      auto uginc = [](auto px, auto pa, auto tt){
        // insure convergence in each case for all members of simd vector
        // making x =  a <  a+1 when the tt do not succeed
        px = if_else(tt, px, inc(pa));
        // Continued fraction for x >= a+1
        // k = find(a ~= 0 & x >= a+1); % & x ~= 0
        auto x0   = one(as(px));
        auto x1   = px;
        auto b0   = zero(as(px));
        auto b1   = x0;
        auto fac  = rec[pedantic](x1);
        auto n    = one(as(px));
        auto g    = b1 * fac;
        auto gold = b0;

        while( maximum(abs(g - gold)) >= 100 * eve::epsilon(maximum(eve::abs(g))) )
        {
          gold     = g;
          auto ana = n - pa;
          x0       = fma(x0, ana, x1) * fac;
          b0       = fma(b0, ana, b1) * fac;
          auto anf = n * fac;
          x1       = fma(px, x0, anf * x1);
          b1       = fma(px, b0, anf * b1);
          fac      = rec[pedantic](x1);
          g        = b1 * fac;
          n        = inc(n);
        }
        return if_else(eve::is_infinite(px), one, oneminus(exp(-px + pa * log(px) - log_abs_gamma(pa)) * g));
      };

      test    = x < inc(a);
      notdone = next_interval(lginc, notdone, test, res, x, a, test);
      if( eve::any(notdone) ) last_interval(uginc, notdone, res, x, a, !test);
      return res;
    }
  }
}
