//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/math/regular/atan.hpp>
#include <eve/module/math/regular/sinh.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto gd_(EVE_SUPPORTS(cpu_)
                                     , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return atan(sinh(x));
    }
    else return apply_over(gd, x);
  }
}
