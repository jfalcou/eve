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

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/atan2.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/radindeg.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto atan2d_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    return arithmetic_call(atan2d, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto atan2d_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  requires  has_native_abi_v<T>
  {
    return radindeg(atan2(a, b));
  }
}
