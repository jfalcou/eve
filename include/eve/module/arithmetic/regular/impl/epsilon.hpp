//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/abs.hpp>
#include <eve/module/arithmetic/regular/next.hpp>
#include <eve/module/arithmetic/regular/dist.hpp>
#include <eve/module/arithmetic/regular/is_nan.hpp>

namespace eve::detail
{
  template<real_value T> EVE_FORCEINLINE constexpr T epsilon_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto aa = abs(a);
      return if_else(is_nan(a), allbits, dist(aa, next(aa)));
    }
    else
    {
      return apply_over(eve::epsilon, a);
    }
  }
}
