//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/arithmetic.hpp>
#include <eve/module/math/pedantic/atan2.hpp>
#include <eve/module/math/regular/radinpi.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  atan2pi_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
  {
    return arithmetic_call(pedantic(atan2pi), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto
  atan2pi_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return radinpi(pedantic(atan2)(a, b));
  }
}
