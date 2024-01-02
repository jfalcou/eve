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
  auto  hypot_(EVE_SUPPORTS(cpu_), pedantic_type const&, T0 x, T1 y)
    -> decltype(hypot(x, y))
  {
    using r_t = decltype(hypot(x, y));
    if constexpr( has_native_abi_v<r_t> )
    {
      using eve::abs;
      r_t ax(abs(x));
      r_t ay(abs(y));
      auto test = ax > ay;
      eve::swap_if(test, ax, ay); // now 0 <= ax <= ay

      auto scale = if_else(ax > sqrtvalmax(as(ax)), sqrtsmallestposval(as<r_t>())/4
                          , if_else(ay < sqrtsmallestposval(as(ay)), rec(sqrtsmallestposval(as<r_t>())/4)
                                   ,  one)
                          );
      ax *= scale;
      ay *= scale;
      auto h = sqrt(fma(ax,ax,ay*ay));
      auto h2 = sqr(h);
      auto ax2 = sqr(ax);
      auto x = fma(-ay,ay,h2-ax2) + fma(h,h,-h2) - fma(ax,ax,-ax2);
      h-= x/(2*h);
      h /= scale;
      h = if_else(is_eqz(ay), zero, h);
      h = if_else(ax <= ay*eve::sqrteps(as<r_t>()), ay, h);
      h = if_else(is_infinite(ax) || is_infinite(ay), inf(as<r_t>()), h);
      return h;
    }
    else { return apply_over(pedantic(hypot), r_t(x), r_t(y)); }
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
