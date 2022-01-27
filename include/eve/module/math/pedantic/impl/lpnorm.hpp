//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/core/detail/generic/horn.hpp>

namespace eve::detail
{
  template<real_value P, floating_value T0, floating_value T1, floating_value ...Ts>
  auto lpnorm_(EVE_SUPPORTS(cpu_), pedantic_type const &
              , const P & p, T0 a0, T1 a1, Ts... args) ->  common_compatible_t<T0,T1,Ts...>
  {
    if constexpr(integral_value<P>)
    {
      auto fp = floating_(p);
      return pedantic(lpnorm)(fp, a0, a1, args...);
    }
    else
    {
      using r_t = common_compatible_t<T0,T1,Ts...>;

      if constexpr(has_native_abi_v<r_t>)
      {
        if (eve::all(p == P(2))) return pedantic(hypot)(r_t(a0), r_t(a1), r_t(args)...);
        else if (eve::all(p == P(1))) return pedantic(manhattan)(r_t(a0), r_t(a1), r_t(args)...);
        else if (eve::all(p == eve::inf(as(p)))) return numeric(maxabs)(r_t(a0), r_t(a1), r_t(args)...);
        else
        {
          auto rp =  r_t(p);
          auto e = -maxmag(exponent(r_t(a0)), exponent(r_t(a1)), exponent(r_t(args))...);
          r_t that(pow_abs(pedantic(ldexp)(r_t(a0), e), rp));
          auto inf_found = is_infinite(r_t(a0));
          auto addppow = [&inf_found, rp, e](auto that, auto next)->r_t{
            inf_found = inf_found || is_infinite(next);
            next = pedantic(ldexp)(next, e);
            that +=  pow_abs(next, rp);
            return that;
          };
          that = addppow(that,r_t(a1));
          auto isinfp = is_infinite(rp);
          if (eve::any(isinfp))
          {
            auto r = numeric(maxabs)(r_t(a0), r_t(a1), r_t(args)...);
            if (eve::all(isinfp)) return r;
            ((that = addppow(that,r_t(args))),...);
            return if_else(isinfp, r,  if_else(inf_found, inf(as<r_t>()),
                                               pedantic(ldexp)(pow_abs(that, rec(rp)), -e)));
          }
          ((that = addppow(that,r_t(args))),...);
          that = if_else(inf_found, inf(as<r_t>()),  pedantic(ldexp)(pow_abs(that, rec(rp)), -e));
          return that;
        }
      }
      else
      {
        return apply_over(pedantic(lpnorm), p, a0, a1, args...);
      }
    }
  }
}
