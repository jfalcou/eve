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
  template<real_value T0, real_value ...Ts>
  auto hypot_(EVE_SUPPORTS(cpu_), pedantic_type const &, T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    if constexpr(has_native_abi_v<r_t>)
    {
      auto e = -maxmag(exponent(r_t(a0)), exponent(r_t(args))...);
      r_t that(sqr_abs(pedantic(ldexp)(r_t(a0), e)));
      auto inf_found = is_infinite(that);
      auto addsqrabs = [&inf_found, e](auto that, auto next)->r_t{
        inf_found = inf_found || is_infinite(next);
        next = pedantic(ldexp)(r_t(next), e);
        if constexpr(real_value < r_t>)
        {
          return fma(next, next, that);
        }
        else
        {
          return sqr_abs(next)+ that;
        }
      };
      ((that = addsqrabs(that,r_t(args))),...);
      return if_else(inf_found, inf(as<r_t>()), pedantic(ldexp)(eve::sqrt(that), -e));
    }
    else
    {
      return apply_over(pedantic(hypot), r_t(a0), r_t(args)...);
    }
  }
}
