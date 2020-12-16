//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/function/saturated/max.hpp>
#include <eve/function/saturated.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(saturated_type(minmag), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto maxmag_(EVE_SUPPORTS(cpu_), saturated_type const &, T const &a, T const &b) noexcept
  {
    auto aa  = saturated(eve::abs)(a);
    auto bb  = saturated(eve::abs)(b);
    if constexpr( simd_value<T> )
    {
      auto tmp = if_else(is_not_greater_equal(aa, bb), b, saturated(eve::max)(a, b));
      return if_else(is_not_greater_equal(bb, aa), a, tmp);
    }
    else
    {
      return aa < bb ? b : bb < aa ? a : saturated(eve::max)(a, b);
    }
  }
}
