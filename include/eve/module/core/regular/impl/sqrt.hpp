//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/is_gtz.hpp>
#include <eve/module/core/regular/prev.hpp>
#include <eve/module/core/regular/next.hpp>
#include <cmath>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T sqrt_(EVE_REQUIRES(cpu_),
                                    O const& o,
                                    T const& a0) noexcept
  {
    if constexpr( O::contains(lower) || O::contains(upper))
    {
     if constexpr(O::contains(strict))
      {
        auto r = sqrt[o.drop(lower, upper, strict)](a0);
        if constexpr(O::contains(lower))
          return prev(r);
        else
          return next(r);
      }
      else
      {
        auto x = sqrt[o.drop(lower, upper)](a0);
        auto [r, e] = two_prod(x, x);
        if constexpr(O::contains(lower))
          return eve::prev[r > a0 || (r == a0 && eve::is_gtz(e))](x);
        else
          return eve::next[r < a0 || (r == a0 && eve::is_ltz(e))](x);
      }
    }
    else if constexpr( scalar_value<T> )
      return std::sqrt(a0);
    else
      return map_pt(as<T>{}, eve::sqrt, a0);
  }
}
