//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/pow.hpp>
#include <eve/module/math/regular/expm1.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  auto powm1_(EVE_SUPPORTS(cpu_),
                              T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(powm1, a, b);
  }

  template<floating_real_value T>
  auto powm1_(EVE_SUPPORTS(cpu_),
                              T const &x, T const &y) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      T r = dec(pow(x, y));
      auto test = (abs(y * dec(x)) < T(0.5) || (abs(y) < T(0.2)));
      if ( eve::any(test) )
      {
        // We don't have any good/quick approximation for log(x) * y
        // so just try it and see:
        auto l = y * log(abs(x));
        auto tmp0 = expm1(l);
        auto tmp1 = if_else(is_ltz(x) && is_odd(x), -tmp0, tmp0);
        return if_else(l < T(0.5), tmp1, r);
      }
      else return r;
    }
    else
      return apply_over(powm1, x, y);
  }

}
