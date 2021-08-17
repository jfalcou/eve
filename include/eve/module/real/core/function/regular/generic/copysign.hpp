//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/constant/signmask.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE  auto copysign_(EVE_SUPPORTS(cpu_)
                            , T a
                            , U b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(copysign, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T copysign_(EVE_SUPPORTS(cpu_)
                              , T a
                              , T b) noexcept
  requires has_native_abi_v<T>
  {
    return bit_or(bitofsign(b), bit_notand(signmask(eve::as(a)), a));
  }
}
