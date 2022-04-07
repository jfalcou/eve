//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  
  template<real_value T0, real_value U0, real_value T1, real_value U1, real_value ...Ts>
  auto sum_of_prod_(EVE_SUPPORTS(cpu_), T0 a0, U0 b0, T1 a1, U1 b1, Ts... args)
    requires (compatible_values<T0, Ts> && ...)
  {
    EVE_ASSERT(!((sizeof...(Ts))&1),"total number of parameters must be even");
    using r_t = common_compatible_t<T0,U0, T1, U1, Ts...>;
    auto sop = [](auto a, auto b, auto c,  auto d){
      auto mcd = -c * d;
      auto err = fma(c, d, mcd);
      auto dop = fms(a, b, mcd);
      return dop + err;
    };

    r_t that(sop(r_t(a0), r_t(b0), r_t(a1), r_t(b1)));
    if constexpr(sizeof...(Ts) == 0)
      return that;
    else
    {
      auto  b(false);
      r_t tmp;
      auto step = [&b, &tmp](auto it, auto arg){
        it = fam[b](it, tmp, r_t(arg));
        tmp =  r_t(arg);
        b = !b;
        return it;
      };
      ((that = step(that,args)),...);
      return that;
    }
  }

}
