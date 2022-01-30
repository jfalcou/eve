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
#include <eve/module/arithmetic/pedantic/min.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), pedantic_type const &
                              , T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(pedantic(minmag), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), pedantic_type const &
                              , T const &a, T const &b) noexcept
  {
    auto aa  = saturated(eve::abs)(a);
    auto bb  = saturated(eve::abs)(b);
    if constexpr( simd_value<T> )
    {
      auto tmp = if_else(is_not_greater_equal(bb, aa), b, pedantic(eve::min)(a, b));
      return if_else(is_not_greater_equal(aa, bb), a, tmp);
    }
    else
    {
      return aa < bb ? a : bb < aa ? b : pedantic(eve::min)(a, b);
    }
  }
}
