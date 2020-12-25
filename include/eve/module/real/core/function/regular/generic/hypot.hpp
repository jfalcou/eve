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
#include <eve/function/fma.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  template<real_value T0, real_value ...Ts>
  auto hypot_(EVE_SUPPORTS(cpu_), pedantic_type const &, T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    if constexpr(has_native_abi_v<r_t>)
    {
      auto e = -maxmag(exponent(a0), exponent(args)...);
      r_t that(sqr(pedantic(ldexp)(a0, e)));
      auto inf_found = is_infinite(that);
      auto addsqr = [&inf_found, e](auto that, auto next)->r_t{
        inf_found = inf_found || is_infinite(next);
        next = pedantic(ldexp)(next, e);
        that = fma(next, next, that);
        return that;
      };
      ((that = addsqr(that,args)),...);
      return if_else(inf_found, inf(as<r_t>()), ldexp(eve::sqrt(that), -e));
    }
    else
    {
      return apply_over(pedantic(hypot), a0, args...);
    }
  }

  template<real_value T0, real_value ...Ts>
  common_compatible_t<T0,Ts...> hypot_(EVE_SUPPORTS(cpu_), T0 a0, Ts... args)
  {
    using r_t = common_compatible_t<T0,Ts...>;
    if constexpr(has_native_abi_v<r_t>)
    {
      r_t that(sqr(eve::abs(a0)));
      auto addsqr = [](auto that, auto next)->r_t{
        that = fma(next, next, that);
        return that;
      };
      ((that = addsqr(that,args)),...);
      return eve::sqrt(that);
    }
    else
    {
      return apply_over(hypot, a0, args...);
    }
  }
}
