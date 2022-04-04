//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T radindeg_(EVE_SUPPORTS(cpu_)
                                       , diff_type<1> const &
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return radindeg(one(as(a)));
    }
    else return apply_over(radindeg, a);
  }
}
