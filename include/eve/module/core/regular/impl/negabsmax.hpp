//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/absmax.hpp>
#include <eve/module/core/regular/minus.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  negabsmax_(EVE_REQUIRES(cpu_), O const & o, T0 r0, T1 r1, Ts... rs) noexcept
  {
    if constexpr(O::contains(saturated2))
    {
      auto tmp1 =  rbr::drop(saturated2, o);
      auto omax = options<decltype(tmp1)>{tmp1};

      return minus(absmax[omax](r0, r1, rs...));
    }
    else
      return minus(absmax[o](r0, r1, rs...));
  }

  //================================================================================================
  // tuples
  //================================================================================================
  template<kumi::non_empty_product_type Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  negabsmax_(EVE_REQUIRES(cpu_), O const & o, Ts tup) noexcept
  //  requires (kumi::size_v<Ts> >=  2)
  {
    return kumi::apply( [&](auto... a) { return eve::negabsmax[o](a...); }, tup);
  }
}
