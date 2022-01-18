//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>

namespace eve::detail
{
  template<real_value T0, real_value ...Ts>
  common_compatible_t<T0,Ts...> hypot_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    if constexpr(has_native_abi_v<r_t>)
    {
      r_t that(sqr_abs(r_t(a0)));
      auto addsqrabs = [](auto that, auto next)->r_t{
        auto anext =  eve::abs(next);
        that = fma(anext, anext, that);
        return that;
      };
      ((that = addsqrabs(that,args)),...);
      return eve::sqrt(that);
    }
    else
    {
      return apply_over(hypot, r_t{a0}, r_t{args}...);
    }
  }
}
