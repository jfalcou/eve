//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/max.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/manhattan.hpp>
#include <eve/function/max.hpp>
#include <eve/function/pow_abs.hpp>
#include <eve/function/rec.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/constant/inf.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{

  template<real_value P, floating_value T0, floating_value ...Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), const P & p, T0 a0, Ts... args)
    requires(!decorator<P>)
  {
////      std::cout << "+++ p " << p << std::endl;
    if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return lpnorm(fp, a0, args...);
    }
    else
    {
////        std::cout << " === p " << p << std::endl;
      if (all(p == P(2))) return hypot(a0, args...);
      else if (all(p == P(1))) return manhattan(a0, args...);
      else if (all(p == eve::inf(as(p)))) return max(abs(a0), abs(args)...);
      else
      {
////      std::cout << "*** p " << p << std::endl;
        using r_t = common_compatible_t<T0,Ts...>;
        if constexpr(has_native_abi_v<r_t>)
        {
          auto rp =  r_t(p);
          r_t that(sqr(eve::abs(a0)));
          auto addppow = [rp](auto that, auto next)->r_t{
            that +=  pow_abs(next, rp);
            return that;
          };
          ((that = addppow(that,args)),...);
          auto isinfp = is_infinite(rp);
          if (any(isinfp))
          {
            auto r = max(abs(a0), abs(args)...);
            if (all(isinfp)) return r;
            return if_else(isinfp, r, pow_abs(that, rec(rp)));
          }
          return pow_abs(that, rec(rp));
        }
        else
        {
          return apply_over(lpnorm, a0, args...);
        }
      }
    }
  }
}
