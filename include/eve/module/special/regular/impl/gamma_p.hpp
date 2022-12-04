//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{

template<floating_value T, floating_value U>
EVE_FORCEINLINE auto
gamma_p_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
-> common_value_t<T, U>
{
  return arithmetic_call(gamma_p, a, b);
}

template<floating_ordered_value T>
T
gamma_p_(EVE_SUPPORTS(cpu_), T x, T a) noexcept requires has_native_abi_v<T>
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
  auto lginc = [](auto a0, auto a1, auto test)
  {
    // insure convergence in each case for all members of simd vector
    // making x = a+1 when the test do not succeed
    auto x = if_else(test, a0, a1);

    // Series expansion for x < a+1
    auto ap  = a1;
    auto del = one(as(ap));
    auto sum = del;

    while( eve::any(abs(del) >= T(100) * epsilon(maximum(abs(sum)))) )
    {
      ap += one(as(ap));
      del = x * del / ap;
      sum += del;
    }
    auto b = sum * eve::exp(fms(a1, eve::log(x), eve::log_abs_gamma(inc(a1)) + x));
    //  For very small a, the series may overshoot very slightly.
    b = eve::min(b, one(as(b)));
    //  if lower, b(k) = bk; else b(k) = 1-bk; end
    return if_else(is_eqz(a0) && is_eqz(a1), one, b);
  };
  auto uginc = [](auto x, auto a, auto test)
  {
    // insure convergence in each case for all members of simd vector
    // making x =  a <  a+1 when the test do not succeed
    x = if_else(test, x, inc(a));
    // Continued fraction for x >= a+1
    // k = find(a ~= 0 & x >= a+1); % & x ~= 0
    auto x0   = one(as(x));
    auto x1   = x;
    auto b0   = zero(as(x));
    auto b1   = x0;
    auto fac  = rec(x1);
    auto n    = one(as(x));
    auto g    = b1 * fac;
    auto gold = b0;

    while( maximum(abs(g - gold)) >= 100 * eve::epsilon(maximum(eve::abs(g))) )
    {
      gold     = g;
      auto ana = n - a;
      x0       = fma(x0, ana, x1) * fac;
      b0       = fma(b0, ana, b1) * fac;
      auto anf = n * fac;
      x1       = fma(x, x0, anf * x1);
      b1       = fma(x, b0, anf * b1);
      fac      = rec(x1);
      g        = b1 * fac;
      n        = inc(n);
    }
    return if_else(eve::is_infinite(x), one, oneminus(exp(-x + a * log(x) - log_abs_gamma(a)) * g));
  };

  test    = x < inc(a);
  notdone = next_interval(lginc, notdone, test, res, x, a, test);
  if( eve::any(notdone) ) last_interval(uginc, notdone, res, x, a, !test);
  return res;
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C,  typename T0, typename ... Ts>
EVE_FORCEINLINE auto
gamma_p_(EVE_SUPPORTS(cpu_), C const& cond, T0 t0, Ts ... ts) noexcept
-> decltype(if_else(cond, gamma_p(t0, ts...), t0))
{
  return mask_op(cond, eve::gamma_p, t0, ts ...);
}

template<conditional_expr C, decorator D,  typename T0, typename  ... Ts>
EVE_FORCEINLINE auto
gamma_p_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, T0 t0, Ts ... ts) noexcept
-> decltype(if_else(cond, gamma_p(t0, ts...), t0))
{
  return mask_op(cond, d(eve::gamma_p), t0, ts ...);
}
}
