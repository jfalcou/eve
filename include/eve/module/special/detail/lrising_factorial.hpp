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
#include <eve/module/special/regular/digamma.hpp>
#include <eve/module/special/regular/log_abs_gamma.hpp>

namespace eve::detail
{

template<floating_ordered_value T>
EVE_FORCEINLINE auto
inner_lrising_factorial(T a, T x) noexcept
{
  // Assumes a>0 and a+x>0.
  auto ax      = eve::abs(x);
  auto notdone = is_nlez(a) && is_nlez(a + x);
  auto r       = nan(as(x));
  auto lr0     = [](auto a, auto x) { return log_abs_gamma(x + a) - log_abs_gamma(a); };

  auto lr1 = [](auto a, auto x)
  {
    const auto xoa = x / a;
    const auto den = inc(xoa);
    const auto d2  = sqr(den);
    const auto d3  = den * d2;
    const auto d5  = d3 * d2;
    const auto d7  = d5 * d2;
    const auto c1  = -xoa / den;
    const auto c3  = -xoa * (3 + xoa * (3 + xoa)) / d3;
    const auto c5  = -xoa * (5 + xoa * (10 + xoa * (10 + xoa * (5 + xoa)))) / d5;
    const auto c7 =
        -xoa * (7 + xoa * (21 + xoa * (35 + xoa * (35 + xoa * (21 + xoa * (7 + xoa)))))) / d7;
    const auto p8    = eve::pow(inc(xoa), 8);
    const auto c8    = dec(rec(p8));            /* these need not   */
    const auto c9    = dec(rec(p8 * inc(xoa))); /* be very accurate */
    const auto a2    = sqr(a);
    const auto a4    = sqr(a2);
    const auto a6    = a4 * a2;
    const auto ser_1 = c1 + c3 / (30 * a2) + c5 / (105 * a4) + c7 / (140 * a6);
    const auto ser_2 = c8 / (99 * a6 * a2) - 691 * c9 / (a6 * a4) / 360360;
    const auto ser   = (ser_1 + ser_2) / (12 * a);
    auto       term1 = x * dec(eve::log(a)); // eve::log(a/M_E);
    auto       lg    = eve::log1p(xoa);
    auto       term2 = (x + a - half(as(x))) * lg;
    return term1 + term2 + ser;
  };

  auto lr2 = [](auto a, auto x)
  {
    return if_else(dist(x + a, a) < 10 * a * eps(as(a)),
                   eve::log1p(x * digamma(a)),
                   log_abs_gamma(a + x) - log_abs_gamma(a));
  };

  if( eve::any(notdone) )
  {
    auto test0 = (10 * ax > a) || (10 * ax * log(eve::max(a, T(2))) > one(as(x)));
    notdone    = next_interval(lr0, notdone, test0, r, a, x);
    if( eve::any(notdone) )
    {
      auto test1 = (10 * ax <= a) && (a > T(15));
      notdone    = next_interval(lr1, notdone, test1, r, a, x);
      if( eve::any(notdone) ) { notdone = last_interval(lr2, notdone, r, a, x); }
    }
  }
  return r;
}
}
