//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/pow.hpp>
#include <eve/module/math/regular/log1p.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  /*EVE_FORCEINLINE*/ auto pow1p_(EVE_SUPPORTS(cpu_),
                              T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pow1p, a, b);
  }

  template<floating_real_value T>
  /*EVE_FORCEINLINE*/ auto pow1p_(EVE_SUPPORTS(cpu_),
                              T const &x, T const &y) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      T incx = inc(x);
      return if_else(abs(x) > half(as(x)), pow(incx, y), exp(y*log1p(x)));
    }
    else
      return apply_over(pow1p, x, y);
  }

}
