//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{
  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::cbrt_, Z const& a) noexcept
  {
    if constexpr(has_native_abi_v<Z>)
    {
      auto pos = is_gtz(a);
      auto [r, e] = frexp(abs(a ));
      auto ee = int_(e);
      auto test = is_nez(ee-3*(ee/3));
      while ( eve::any(test) )
      {
        ee = inc[test](ee);
        r = if_else(test, ldexp(r,-1), r);
        test = is_nez(ee-3*(ee/3));
      }
      Z x(rec(cbrt(high(r))));
      x += x * oneminus(r * sqr(x) * x) * third(as(x));
      x += x * oneminus(r * sqr(x) * x) * third(as(x));
      x = rec(x);
      x = if_else(pos, x, -x);
      auto xx = ldexp( x, ee / 3 );
      return  if_else ( is_not_finite( a ) || is_eqz( a ), a, xx);
    }
    else return apply_over(cbrt, a);
  }

}
