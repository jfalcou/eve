//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/log_2.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/expm1.hpp>
#include <eve/module/math/regular/log.hpp>
#include <eve/module/math/regular/log1p.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  logspace_sub_(EVE_REQUIRES(cpu_), O const &, T0 a0, T1 a1, Ts... args) noexcept
  {
    using r_t = common_value_t<T0, T1, Ts...>;
    if constexpr(sizeof...(Ts) == 0)
    {
      if constexpr( has_native_abi_v<T0> )
      {
        auto r0 = r_t(a0);
        auto r1 = r_t(a1);
        auto x    = r1-r0;
        auto test = x > -log_2(as(x));
        if( eve::all(test) )
          return r0 + eve::log(-expm1(x));
        else if( eve::any(test) )
          return r0+ if_else(test, log(-expm1(x)), log1p(-exp(x)));
        else
          return r0 + log1p(-exp(x));
      }
      else return arithmetic_call(logspace_sub, r_t(a0), r_t(a1));
    }
    else
    {
      r_t  that(logspace_sub(a0, a1));
      auto lsub = [](auto that, auto next) -> r_t
        {
          that = logspace_sub(that, next);
          return that;
        };
      ((that = lsub(that, args)), ...);
      return that;
    }
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  auto
  logspace_sub_(EVE_REQUIRES(cpu_), O const &, Ts const& tup) noexcept
  {
    if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
    else return kumi::apply( [&](auto... m) { return logspace_sub(m...); }, tup);
  }

}
