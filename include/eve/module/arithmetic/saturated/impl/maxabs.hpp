//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/saturated/abs.hpp>
#include <eve/module/arithmetic/regular/max.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto maxabs_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(saturated(maxabs), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto maxabs_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return  max(saturated(eve::abs)(a), saturated(eve::abs)(b));
  }
}
