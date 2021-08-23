//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/all.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/max.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/manhattan.hpp>
#include <eve/function/maxabs.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/rec.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/constant/inf.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{

  template<real_value P, floating_value T0, floating_value T1, floating_value ...Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), const P & p, T0 a0, T1 a1, Ts... args)
    requires(!decorator<P>)
  {
    if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return lpnorm(fp, a0, a1, args...);
    }
    else
    {
      using r_t = common_compatible_t<T0,T1,Ts...>;
      if constexpr(has_native_abi_v<r_t>)
      {
        if (eve::all(p == P(2))) return hypot(r_t(a0), r_t(a1), r_t(args)...);
        else if (eve::all(p == P(1))) return manhattan(r_t(a0), r_t(a1), r_t(args)...);
        else if (eve::all(p == eve::inf(as(p)))) return eve::maxabs(r_t(a0), r_t(a1), r_t(args)...);
        else
        {
          auto rp =  r_t(p);
          r_t that(pow_abs(r_t(a0), rp));
          auto addppow = [rp](auto that, auto next)->r_t{
            that +=  pow_abs(next, rp);
            return that;
          };
          that = addppow(that,  r_t(a1));
          ((that = addppow(that,args)),...);
          auto isinfp = is_infinite(rp);
          if (eve::any(isinfp))
          {
            auto r = eve::max(eve::abs(r_t(a0)), eve::abs(r_t(a1)), eve::abs(r_t(args))...);
            if (eve::all(isinfp)) return r;
            return if_else(isinfp, r, pow_abs(that, rec(rp)));
          }
          return pow_abs(that, rec(rp));
        }
      }
      else
      {
        return apply_over(lpnorm, p, a0, a1, args...);
      }
    }
  }
}
