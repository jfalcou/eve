//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/sinh.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE auto csch_(EVE_SUPPORTS(cpu_)
                            , T const &a0) noexcept
  {
    if constexpr(has_native_abi_v<T>) return rec(sinh(a0));
    else                    return apply_over(csch, a0);
  }
}
