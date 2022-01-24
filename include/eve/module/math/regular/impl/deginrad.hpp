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

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T deginrad_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto ridh  = Ieee_constant<T, 0x3c8ef000U,  0x3f91df46a0000000ll>();
      auto ridl  = Ieee_constant<T, 0x36a35129U,  0x3de294e9c8ae0ec6ll>();
      return fma(a, ridl, a*ridh);
    }
    else return apply_over(deginrad, a);
  }
}
