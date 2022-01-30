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
#include <eve/module/arithmetic/regular/is_nan.hpp>
#include <eve/module/arithmetic/regular/is_not_greater_equal.hpp>
#include <eve/module/arithmetic/pedantic/max.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto maxabs_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(maxabs), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto maxabs_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, T const &b) noexcept
  {
    return  pedantic(max)(eve::abs(a), eve::abs(b));
  }
}
