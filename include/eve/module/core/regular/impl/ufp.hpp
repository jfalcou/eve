//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/bit_floor.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T ufp_(EVE_SUPPORTS(cpu_)
                                 , T v) noexcept
  {
    return bit_floor(abs(v));
  }
}
