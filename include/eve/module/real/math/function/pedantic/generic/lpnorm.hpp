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
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/pedantic/max.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/pedantic/manhattan.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/pedantic/ldexp.hpp>
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
  auto lpnorm_(EVE_SUPPORTS(cpu_), pedantic_type const &
              , const P & p, T0 a0, Ts... args)
  {
    if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return pedantic(lpnorm)(fp, a0, args...);
    }
    else
    {
      using r_t = common_compatible_t<T0,Ts...>;
      if constexpr(has_native_abi_v<r_t>)
      {
        if (all(p == P(2))) return pedantic(hypot)(r_t(a0), r_t(args)...);
        else if (all(p == P(1))) return pedantic(manhattan)(r_t(a0), r_t(args)...);
        else if (all(p == eve::inf(as(p)))) return pedantic(max)(abs(r_t(a0)), abs(r_t(args))...);
        else
        {
          auto rp =  r_t(p);
          if constexpr(has_native_abi_v<r_t>)
          {
            auto e = -maxmag(exponent(r_t(a0)), exponent(r_t(args))...);
            r_t that(pow_abs(pedantic(ldexp)(r_t(a0), e), rp));
            auto inf_found = is_infinite(r_t(a0));
            auto addppow = [&inf_found, rp, e](auto that, auto next)->r_t{
              inf_found = inf_found || is_infinite(next);
              next = pedantic(ldexp)(next, e);
              that +=  pow_abs(next, rp);
              return that;
            };
            auto isinfp = is_infinite(rp);
            if (any(isinfp))
            {
              auto r = pedantic(max)(abs(r_t(a0)), abs(r_t(args))...);
              if (all(isinfp)) return r;
              ((that = addppow(that,r_t(args))),...);
              return if_else(isinfp, r,  if_else(inf_found, inf(as<r_t>()),
                                                 pedantic(ldexp)(pow_abs(that, rec(rp)), -e)));
            }
            ((that = addppow(that,r_t(args))),...);
            that = if_else(inf_found, inf(as<r_t>()),  pedantic(ldexp)(pow_abs(that, rec(rp)), -e));
            return that;
          }
          else
          {
            return apply_over(pedantic(lpnorm), a0, args...);
          }
        }
      }
    }
  }
}
