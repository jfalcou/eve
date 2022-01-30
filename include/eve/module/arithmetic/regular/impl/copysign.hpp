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
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto copysign_(EVE_SUPPORTS(cpu_)
                            , T a
                            , U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(copysign, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T copysign_(EVE_SUPPORTS(cpu_)
                              , T a
                              , T b) noexcept
  requires has_native_abi_v<T>
  {
    return bit_or(bitofsign(b), bit_notand(signmask(eve::as(a)), a));
  }
}
