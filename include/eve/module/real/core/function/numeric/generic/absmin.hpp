//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/numeric/min.hpp>
#include <eve/function/numeric.hpp>
#include <eve/platform.hpp>

#include <type_traits>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto absmin_(EVE_SUPPORTS(cpu_), numeric_type const &
                              , T const &a, U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(numeric(absmin), a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto absmin_(EVE_SUPPORTS(cpu_), numeric_type const &
                              , T const &a, T const &b) noexcept
  {
    return eve::abs(numeric(eve::min)(a, b));
  }

  //================================================================================================
  //N parameters
  //================================================================================================
  template<real_value T0, real_value T1, real_value ...Ts>
  auto absmin_(EVE_SUPPORTS(cpu_), numeric_type const &, T0 a0, T1 a1, Ts... args)
  {
    return eve::abs(numeric(eve::min)(a0, a1, args...));
  }

}
