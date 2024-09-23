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
                                    O const&,
                                    T const& a0) noexcept
  {
    if constexpr( O::contains(lower) || O::contains(upper))
    {
      using namespace spy::literal;
      if constexpr( enable_roundings)
      {
        return with_rounding<O>(eve::sqrt, a0);
      }
      else
      {
        auto x = sqrt(a0);
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
      return map(eve::sqrt, a0);
  }
}
