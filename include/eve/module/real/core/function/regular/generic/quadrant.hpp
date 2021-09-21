//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/floor.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<real_value T>
  EVE_FORCEINLINE constexpr T quadrant_(EVE_SUPPORTS(cpu_)
                                       , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(floating_value<T>)
      {
        T b = a*T(0.25);
        return (b-floor(b))*T(4);
      }
      else if constexpr(integral_value<T>)
        return (a & T(3));
    }
    else
      return apply_over(quadrant, a);
  }
}
