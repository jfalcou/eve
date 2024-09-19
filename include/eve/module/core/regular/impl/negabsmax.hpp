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
    if constexpr(O::contains(saturated))
    {
      auto tmp1 =  rbr::drop(saturated, o);
      auto omax = options<decltype(tmp1)>{tmp1};

      return minus(absmax[omax](r0, r1, rs...));
    }
    else
      return minus(absmax[o](r0, r1, rs...));
  }
}
