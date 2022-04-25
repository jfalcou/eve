//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/bit_floor.hpp>
#include <eve/module/math/constant/halfeps.hpp>
#include <iostream>
#include <iomanip>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T ufp_(EVE_SUPPORTS(cpu_)
                                 , T v) noexcept
  {
    //if no overflow !
    auto q = inc(rec(eps(as(v))))*v;
    auto z = oneminus(halfeps(as(v)))*q;
    return abs(q-z);
  }
}
