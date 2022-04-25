//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once


#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/regular/ufp.hpp>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T ulp_(EVE_SUPPORTS(cpu_)
                                 , T v) noexcept
  {
    return eps(as(v))*ufp(v);
  }

}
