//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/bit_or.hpp>
#include <eve/module/core/regular/bit_mask.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T add_(EVE_REQUIRES(cpu_), O const&, T a, T b) noexcept
  {
    if constexpr(O::contains(saturated2) && integral_value<T>)
    {
      if constexpr( signed_integral_value<T> )
      {
        auto test = is_ltz(b);
        auto pos  = min(sub(valmax(as(a)), b), a);
        auto neg  = max(sub(valmin(as(a)), b), a);
        return add(b, if_else(test, neg, pos));
      }
      else
      {
        // Triggers conditional MOV that directly read the flag register
        T r = a + b;
        return bit_or(r, bit_mask(is_less(r, a)));
      }
    }
    else
    {
      return a += b;
    }
  }

  template<typename T, std::same_as<T>... Ts, callable_options O>
  EVE_FORCEINLINE constexpr T add_(EVE_REQUIRES(cpu_), O const & o, T r0, T r1, Ts... rs) noexcept
  {
    r0   = add[o](r0,r1);
    ((r0 = add[o](r0,rs)),...);
    return r0;
  }
}
