//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/saturated/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/is_not_greater_equal.hpp>
#include <eve/function/pedantic/max.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/saturated.hpp>
#include <eve/platform.hpp>

#include <type_traits>

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
