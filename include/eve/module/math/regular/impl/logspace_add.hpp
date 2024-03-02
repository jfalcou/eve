//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/exp.hpp>
#include <eve/module/math/regular/log1p.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  logspace_add_(EVE_REQUIRES(cpu_), O const &, T0 a0, T1 a1, Ts... args) noexcept
  {
    using r_t = common_value_t<T0, T1, Ts...>;
    if constexpr(sizeof...(Ts) == 0)
    {
      if constexpr(std::same_as<T0, T1>)
      {
        if constexpr( has_native_abi_v<T0> )
        {
          auto tmp = -eve::abs(a0 - a1);
          auto r   = eve::max(a0, a1) + eve::log1p(eve::exp(tmp));
          if constexpr( eve::platform::supports_invalids )
            r = if_else(is_nan(tmp), a0 + a1, r);
          return r;
        }
        else { return arithmetic_call(logspace_add, a0, a1); }
      }
    }
    else
    {
      r_t  that(logspace_add(a0, a1));
      auto ladd = [](auto that, auto next) -> r_t
        {
          that = logspace_add(that, next);
          return that;
        };
      ((that = ladd(that, args)), ...);
      return that;
    }
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  auto
  logspace_add_(EVE_REQUIRES(cpu_), O const &, Ts tup) noexcept
  {
    if constexpr( kumi::size_v<Ts> == 1) return get<0>(tup);
    else return kumi::apply( [&](auto... m) { return logspace_add(m...); }, tup);
  }

}
