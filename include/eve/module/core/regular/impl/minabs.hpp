//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<typename T0, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, Ts...>
  minabs_(EVE_REQUIRES(cpu_), O const & o, T0 t0, Ts... as) noexcept
  {
    using r_t = eve::common_value_t<T0, Ts...>;
    if constexpr(O::contains(widen))
    {
      if constexpr(signed_integral_value<r_t> && O::contains(saturated))
        return minabs[o.drop(widen)](upgrade(t0), upgrade(as)...);
      else
        return upgrade(minabs[o.drop(widen)](t0, as...));
    }
    else if constexpr(sizeof...(Ts) == 0)
    {
      return abs[o.drop(pedantic,numeric)](r_t(t0));
    }
    else
    {
      auto abso = abs[o.drop(pedantic,numeric)];
      auto r = eve::min[o.drop(saturated)](abso(t0), abso(as)...);
      if constexpr(integral_value<r_t> || !O::contains(pedantic))
        return r;
      else
        return force_if_any(o, r, eve::is_eqz, eve::zero(eve::as(r)), t0, as...);
    }
  }
}
