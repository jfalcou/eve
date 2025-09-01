//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/decorator/core.hpp>

namespace eve::detail
{
  // if option is pedantic and any ts satisfy test value is returned else r
  //
  // This is used in manhattan,  sum_of_squares, hypot and lpnorm.
  template <typename O, typename T, typename ...Ts> auto force_if_any(O, T r, auto test, auto value, Ts...ts)
  {
    using r_t = common_value_t<Ts...>;
    if constexpr(O::contains(pedantic) && floating_value<r_t>)
    {
      auto inf_found =  (test(r_t(ts)) || ...);
      return if_else(inf_found, r_t(value), r);
    }
    else
      return r;
  }
}
