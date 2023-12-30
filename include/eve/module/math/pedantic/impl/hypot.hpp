//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //  This implementation is inspired by
  //  AN IMPROVED ALGORITHM FOR HYPOT(A,B) arXiv:1904.09481v6 [math.NA] 14 Jun 2019, CARLOS F. BORGES
  ////////////////////////////////////////////////////////////////////////////////////////////////////

  template<value T0, value T1>
  auto  hypot_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 a, T1 b)
    -> decltype(hypot(a, b))
  {
    using r_t = decltype(hypot(a, b));
    if constexpr( has_native_abi_v<r_t> )
    {
      r_t aa(abs(a));
      r_t ab(abs(b));
      auto test = aa > ab;
      eve::swap_if(test, aa, ab); // now aa < bb
      auto doit =  [](auto b){    // compute sqrt(1+b*b)
        auto h = sqrt(inc(sqr(b)));
        auto h2 = sqr(h);
        auto x = fma(-b,b,dec(h2)) + fms(h,h,h2);
        return if_else(is_eqz(h), h, h-x/(2*h)); // Maclaurin correction
      };
      auto h = if_else(is_eqz(ab), zero, ab*doit(aa/ab));
      return if_else(is_infinite(a) || is_infinite(b), inf(as<r_t>()), h);
    }
    else { return apply_over(pedantic(hypot), r_t(a), r_t(b)); }
  }

  template<value T0, value T1, value... Ts>
  auto hypot_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 a0, T1 a1, Ts... args)
    -> decltype(hypot(a0, a1, args...))
  {
    using r_t = decltype(hypot(a0, a1, args...));
    if constexpr( has_native_abi_v<r_t> )
    {
      r_t that(pedantic(hypot)(r_t(a0), r_t(a1)));
      ((that = pedantic(hypot)(that, r_t(args))), ...);
      return that;
    }
    else { return apply_over(pedantic(hypot), r_t(a0), r_t(a1), r_t(args)...); }
  }

}
