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
#include <eve/module/special/regular/betainc.hpp>
#include <eve/module/special/regular/lbeta.hpp>
#include <eve/module/special/regular/signgam.hpp>

namespace eve::detail
{
template<floating_value T, floating_value U, floating_value V>
EVE_FORCEINLINE auto
betainc_inv_(EVE_SUPPORTS(cpu_), T x, U a, V b) noexcept requires compatible_values<T, U>
{
  return arithmetic_call(betainc_inv, x, a, b);
}

template<floating_real_value T>
EVE_FORCEINLINE T
betainc_inv_(EVE_SUPPORTS(cpu_), T p, T a, T b) noexcept requires(has_native_abi_v<T>)
{
  auto large = [](auto p, auto a, auto b)
  {
    //  Set initial guess.
    auto const FiveoSix = T(5. / 6.);
    auto       a1       = dec(a);
    auto       b1       = dec(b);
    auto       pp       = oneminus[p >= T(0.5)](p);
    auto       t        = sqrt(-2 * log(pp));
    auto       x =
        fma(t, T(0.27061), T(2.30753)) / fma(t, fma(t, T(0.04481), T(0.99229)), one(as(p))) - t;
    x         = minus[p < T(0.5)](x);
    auto al   = (sqr(x) - T(3)) * T(1.0 / 6.0);
    auto r2a1 = rec(a + a1);
    auto r2b1 = rec(b + b1);
    auto h    = rec(average(r2a1, r2b1));
    auto w    = (x * sqrt(al + h) / h) - (r2b1 - r2a1) * (al + FiveoSix - T(2.0 / 3.0) / h);
    return a / fma(exp(w + w), b, a);
  };

  auto small = [](auto p, auto a, auto b)
  {
    auto lna  = log(a / (a + b));
    auto lnb  = log(b / (a + b));
    auto t    = exp(a * lna) / a;
    auto u    = exp(b * lnb) / b;
    auto w    = t + u;
    auto test = p < t / w;
    auto z    = if_else(test, a * w * p, b * w * oneminus(p));
    auto po   = pow(z, rec(if_else(test, a, b)));
    return if_else(test, po, oneminus(po));
  };
  auto       a1      = dec(a);
  auto       b1      = dec(b);
  auto const o       = one(as(p));
  const auto epsi    = 10 * eps(as(p));
  auto       test    = (a > o) && (b > o);
  auto       x       = nan(as(p));
  auto       notdone = is_not_nan(p);
  notdone            = next_interval(large, notdone, test, x, p, a, b);
  if( eve::any(notdone) ) { last_interval(small, notdone, x, p, a, b); }
  auto afac = -lbeta(a, b);
  ;
  for( std::size_t j = 0; j < 10; ++j )
  {
    auto err = betainc(x, a, b) - p;
    auto t   = exp(fma(a1, log(x), b1 * log1p(-x)) + afac);
    auto u   = err / t; // Halley:
    auto m   = eve::min(o, u * (a1 / x - b1 / (oneminus(x))));
    x -= u / inc(-0.5 * m);
    auto tt = inc[x >= o](t);
    x       = if_else(is_lez(x) && (x >= o), average(x, tt), x);
    if( eve::all(eve::abs(t) <= epsi * x) && j ) break;
  }
  return if_else(is_lez(p), zero, if_else(p >= o, one, x));
}

// -----------------------------------------------------------------------------------------------
// Masked cases
template<conditional_expr C, typename ... Ts>
EVE_FORCEINLINE auto
betainc_inv_(EVE_SUPPORTS(cpu_), C const& cond, Ts ... ts) noexcept
{
  return mask_op(cond, eve::betainc_inv, ts ...);
}

template<conditional_expr C, decorator D, typename  ... Ts>
EVE_FORCEINLINE auto
betainc_inv_(EVE_SUPPORTS(cpu_), C const& cond, D const & d, Ts ... ts) noexcept
{
  return mask_op(cond, d(eve::betainc_inv), ts ...);
}
}
