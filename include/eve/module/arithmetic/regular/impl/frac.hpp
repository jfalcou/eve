//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/trunc.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T>
  EVE_FORCEINLINE auto frac_(EVE_SUPPORTS(cpu_)
                            , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        if constexpr(scalar_value<T>)
        {
          if (!a) return a;
          else return a - trunc(a);
        }
        else
        {
          return if_else(is_eqz(a), a, a - trunc(a));
        }
      }
      else return zero(eve::as(a));
    }
    else return apply_over(frac, a);
  }
}
