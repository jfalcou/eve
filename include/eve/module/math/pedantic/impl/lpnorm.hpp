//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
template<real_value P, floating_value T0, floating_value T1, floating_value... Ts>
auto
lpnorm_(EVE_SUPPORTS(cpu_), pedantic_type const&, const P& p, T0 a0, T1 a1, Ts... args) noexcept
-> decltype(lpnorm(p, a0, a1, args...))
{
  if constexpr( integral_value<P> )
  {
    auto fp = floating_(p);
    return pedantic(lpnorm)(fp, a0, a1, args...);
  }
  else
  {
    using r_t = decltype(lpnorm(p, a0, a1, args...));

    if constexpr( has_native_abi_v<r_t> )
    {
      if( eve::all(p == P(2)) ) return pedantic(hypot)(a0, a1, args...);
      else if( eve::all(p == P(1)) ) return pedantic(manhattan)(a0, a1, args...);
      else if( eve::all(p == eve::inf(as(p))) ) return numeric(maxabs)(a0, a1, args...);
      else
      {
        auto rp = r_t(p);
        auto e  = -maxmag(exponent(r_t(a0)), exponent(r_t(a1)), exponent(r_t(args))...);
        auto f = [&](auto a){return pow_abs(pedantic(ldexp)(r_t(a), e), rp); };
        r_t that = add(f(a0), f(a1), f(args)...);
        auto r = pedantic(ldexp)(pow_abs(that, rec(rp)), -e);
        auto isinfp = is_infinite(rp);
        auto rinf = numeric(maxabs)(a0, a1, args...);
        return if_else(isinfp || is_infinite(rinf), rinf, r);
      }
    }
    else { return apply_over(pedantic(lpnorm), p, r_t(a0), r_t(a1), r_t(args)...); }
  }
}
}
