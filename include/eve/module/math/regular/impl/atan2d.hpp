//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/math/regular/radindeg.hpp>
#include <eve/module/math/regular/atan2.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto atan2d_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    return arithmetic_call(atan2d, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto atan2d_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  requires  has_native_abi_v<T>
  {
    return radindeg(atan2(a, b));
  }
}
