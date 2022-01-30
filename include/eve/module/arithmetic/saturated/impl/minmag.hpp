//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/is_not_greater_equal.hpp>
#include <eve/module/arithmetic/saturated/abs.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(saturated(minmag), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto minmag_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
  {
    auto aa  = saturated(eve::abs)(a);
    auto bb  = saturated(eve::abs)(b);
    if constexpr( simd_value<T> )
    {
      auto tmp = if_else(is_not_greater_equal(bb, aa), b, eve::min(a, b));
      return if_else(is_not_greater_equal(aa, bb), a, tmp);
    }
    else
    {
      return aa < bb ? a : bb < aa ? b : eve::min(a, b);
    }
  }
}
