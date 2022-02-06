//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/module/core/regular/rec.hpp>
#include <eve/module/core/regular/round.hpp>
#include <eve/module/core/saturated/abs.hpp>
#include <eve/module/core/regular/sign.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value S>
  EVE_FORCEINLINE constexpr auto rat_(EVE_SUPPORTS(cpu_)
                                     , T const & x
                                     , S const & tol) noexcept
  requires compatible_values<T, S> && (!std::is_same_v<T, S>)
  {
    using r_t = common_compatible_t<T, S>;
    return rat(r_t(x), r_t(tol));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto rat_(EVE_SUPPORTS(cpu_)
                                     , T const & x
                                     , T const & tol) noexcept
  {
    if (has_native_abi_v<T>)
    {
      auto is_inf = is_infinite(x);
      auto y = if_else(is_inf, zero, x);
      auto n = round(y);
      auto d = one(as(y));
      auto frac = y-n;
      auto lastn = one(as(y));
      auto lastd = zero(as(y));

      while(true)
      {
        auto notdone = is_nez(y) &&  (abs(y - n/d) >= tol);
        if (none(notdone)) break;
        auto flip = if_else(notdone,rec(frac), frac);
        auto step = if_else(notdone,round(flip), zero);
        frac = flip - step;
        auto savedn = n;
        auto savedd = d;
        n = if_else(notdone, fma(n, step,  lastn), n);
        d = if_else(notdone, fma(d, step,  lastd), d);
        lastn = savedn;
        lastd = savedd;
      }
      n *= sign(d);
      d = saturated(abs)(d);
      n = if_else(is_inf, sign(x), n);
      d = if_else(is_inf, zero, d);
      return kumi::tuple<T, T>{n, d};
    }
    else
    {
      return apply_over2(rat, x, tol);
    }
  }

  template<floating_real_scalar_value T>
  EVE_FORCEINLINE constexpr auto rat_(EVE_SUPPORTS(cpu_)
                                     , T const & x
                                     , T const & tol) noexcept
  {
    if (is_infinite(x) || is_eqz(x)) return  kumi::tuple<T, T>{sign(x), 0};
    auto n = round(x);
    auto d = one(as(x));
    auto frac = x-n;
    auto lastn = one(as(x));
    auto lastd = zero(as(x));

    while(abs(x - n/d) >=  tol)
    {
      auto flip = rec(frac);
      auto step = round(flip);
      frac = flip- step;
      auto savedn = n;
      auto savedd = d;
      n = fma(n, step, lastn);
      d = fma(d, step, lastd);
      lastn = savedn;
      lastd = savedd;
    }
    n *= sign(d);
    d = saturated(abs)(d);
     return kumi::tuple<T, T>{n, d};
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto rat_(EVE_SUPPORTS(cpu_)
                                     , T const &x) noexcept
  {
    return rat(x, T(1.0e-6)*eve::abs(x));
  }
}
