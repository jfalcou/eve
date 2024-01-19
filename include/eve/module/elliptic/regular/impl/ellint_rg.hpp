//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/module/core.hpp>
#include <eve/module/elliptic/regular/ellint_rd.hpp>
#include <eve/module/elliptic/regular/ellint_rf.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template<typename T, typename U, typename V, callable_options O>
  constexpr common_value_t<T, U, V>
  ellint_rg_(EVE_REQUIRES(cpu_), O const& o, T x, U y, V z)
  {
    if constexpr(O::contains(raw2))
    {
      if constexpr(std::same_as<T, U> && std::same_as<T, V>)
      {
        swap_if(x < y, x, y);
        swap_if(x < z, x, z);
        swap_if(y > z, y, z);
        // now all(x >= z) and all(z >= y)
        return (z * ellint_rf(x, y, z) - (x - z) * (y - z) *
                ellint_rd(x, y, z) / 3 + sqrt(x * y / z))
          * half(as(x));
      }
      else
        return arithmetic_call(ellint_rg[o], x, y, z);
    }
    else
    {
      auto r       = nan(as(x));
      auto notdone = is_nltz(x) && is_nltz(y) && is_nltz(z);
      // any parameter nan or less than zero implies nan
      auto br0 = [x, y, z]() { return ellint_rg[raw](x, y, z); };
      last_interval(br0, notdone, r);
      return r;
    }
  }
}
