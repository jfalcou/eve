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
#include <eve/module/polynomial.hpp>
#include <eve/module/polynomial/regular/reverse_horner.hpp> //??? why that it is already included by polynomial.hpp

namespace eve::detail
{

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
lambert_serie_utility(T r) noexcept
{
  using elt_t = element_type_t<T>;
  if constexpr( sizeof(elt_t) == 8 )
  {
    constexpr std::array<elt_t, 3> P = {
        0.000000000000000000000e+00,
        2.331643981597117584689e+00,
        1.931973535237478945863e+00,
    };
    constexpr std::array<elt_t, 3> Q = {
        1.000000000000000000000e+00,
        1.605803223118019582808e+00,
        4.174677763382451962312e-01,
    };
    return dec(reverse_horner(r, P) / reverse_horner(r, Q));
  }
  else
  {
    constexpr std::array<elt_t, 2> P = {
        2.33164314895e+00f,
        -1.80949529206e+00f,
    };
    return fam(mone(as(r)), r, eve::reverse_horner(r, P));
  }
}

template<floating_real_value T>
EVE_FORCEINLINE constexpr auto
lambert_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  auto halley = [](auto x, auto w_i, auto max_iters)
  {
    auto w = w_i;
    for( int i = 0; i < max_iters; i++ )
    {
      T e = eve::exp(w);
      T p = inc(w);
      T t = fms(w, e, x);
      t /= if_else(is_gtz(w), e * p, e * p - T(0.5) * inc(p) * t / p);
      w -= t;
      T tol = 10 * eps(as(x)) * eve::max(eve::abs(w), rec(eve::abs(p) * e));
      if( eve::all(eve::abs(t) < tol) ) break;
    }
    return w;
  };

  if constexpr( has_native_abi_v<T> )
  {
    T    q              = x + T(0.367879441171442);
    auto lambert0_small = [](auto q) { // branch 0 q <= 1.0e-3
      return lambert_serie_utility(eve::sqrt(q));
    };
    auto lambert0_other = [&halley](auto x, auto q) { // branch 0 q <= 1.0e'3
      auto p  = eve::sqrt(T(5.436563656918090) * q);
      auto w1 = dec(p * (inc(p * fam(T(-1.0 / 3), p, T(1.0 / 72)))));
      auto w2 = log(x);
      w2 -= if_else(x > 3, zero, log(w2));
      auto init = if_else(x < one(as(x)), w1, w2);
      return halley(x, init, 10);
    };
    auto lambert1 = [&halley](auto x, auto q, auto positivex) { // branch 1 q > 0
      T    r    = -eve::sqrt(q);
      auto test = (x < T(-1.0e-6));
      T    w1(0);
      if( eve::any(test) ) w1 = lambert_serie_utility(r);
      if( eve::all(test) && eve::all(q < T(3.0e-3)) ) return w1;
      T l1 = log(-x);
      T l2 = log(-l1);
      T w2 = l1 - l2 + l2 / l1;
      return if_else(is_eqz(x) && !positivex, minf(as(x)), halley(x, w2, 30));
    };

    auto r       = nan(as<T>());                // nan case treated here
    r            = if_else(is_eqz(x), zero, r); // zero case treated here
    r            = if_else(x == inf(as(x)), x, r);
    auto notdone = is_nlez(q) && (q != inf(as(x)));
    if( eve::any(notdone) )
    {
      notdone = next_interval(lambert0_small, notdone, q < T(1.0e-3), r, q);
      if( eve::any(notdone) ) { notdone = last_interval(lambert0_other, q >= T(1.0e-3), r, x, q); }
    }
    auto positivex = is_positive(x);
    if( eve::all(positivex) ) return kumi::make_tuple(r, r);
    auto r1 = if_else(positivex, r, lambert1(x, q, positivex));
    return kumi::make_tuple(r, r1);
  }
  else return apply_over2(lambert, x);
}

}
