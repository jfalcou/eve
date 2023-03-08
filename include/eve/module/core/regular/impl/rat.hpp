//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/none.hpp>
#include <eve/module/core/regular/rec.hpp>
#include <eve/module/core/regular/round.hpp>
#include <eve/module/core/regular/sign.hpp>
#include <eve/module/core/saturated/abs.hpp>

namespace eve::detail
{
template<ordered_value T, ordered_value S>
EVE_FORCEINLINE constexpr auto
rat_(EVE_SUPPORTS(cpu_),
     T const& x,
     S const& tol) noexcept
-> kumi::tuple<common_value_t<T, S>, common_value_t<T, S>>
 requires (!std::is_same_v<T, S>)
{
  using r_t = common_value_t<T, S>;
  return rat(r_t(x), r_t(tol));
}

template<ordered_value T>
EVE_FORCEINLINE constexpr auto
rat_(EVE_SUPPORTS(cpu_), T const& x, T const& tol) noexcept
{
  if constexpr(scalar_value<T>)
  {
    if( is_infinite(x) || is_eqz(x) ) return kumi::tuple<T, T> {sign(x), 0};
    auto n     = round(x);
    auto d     = one(as(x));
    auto frac  = x - n;
    auto lastn = one(as(x));
    auto lastd = zero(as(x));

    while( abs(x - n / d) >= tol )
    {
      auto flip   = rec(frac);
      auto step   = round(flip);
      frac        = flip - step;
      auto savedn = n;
      auto savedd = d;
      n           = fma(n, step, lastn);
      d           = fma(d, step, lastd);
      lastn       = savedn;
      lastd       = savedd;
    }
    n *= sign(d);
    d = eve::abs(d);
    return kumi::tuple<T, T> {n, d};
  }
  else
  {
    if( has_native_abi_v<T> )
    {
      auto is_inf = is_infinite(x);
      auto y      = if_else(is_inf, zero, x);
      auto n      = nearest(y);
      auto d      = one(as(y));
      auto frac   = y - n;
      auto lastn  = one(as(y));
      auto lastd  = zero(as(y));

      while( true )
      {
        auto notdone = is_nez(y) && (abs(y - n / d) >= tol);
        if( none(notdone) ) break;
        auto flip   = if_else(notdone, rec(frac), frac);
        auto step   = if_else(notdone, nearest(flip), zero);
        frac        = flip - step;
        auto savedn = n;
        auto savedd = d;
        n           = if_else(notdone, fma(n, step, lastn), n);
        d           = if_else(notdone, fma(d, step, lastd), d);
        lastn       = savedn;
        lastd       = savedd;
      }
      n *= sign(d);
      d = abs(d);
      n = if_else(is_inf, sign(x), n);
      d = if_else(is_inf, zero, d);
      return kumi::tuple<T, T> {n, d};
    }
    else { return apply_over2(rat, x, tol); }
  }
}

template<ordered_value T>
EVE_FORCEINLINE constexpr auto
rat_(EVE_SUPPORTS(cpu_), T const& x) noexcept
{
  return rat(x, T(1.0e-6) * eve::abs(x));
}
}
