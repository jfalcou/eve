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
                            , T const &a
                            , U const &b) noexcept
  requires compatible_values<T, U>
  {
    return arithmetic_call(copysign, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE  T copysign_(EVE_SUPPORTS(cpu_)
                              , T const &a
                              , T const &b) noexcept
  requires has_native_abi_v<T>
  {
    return bit_or(bitofsign(b), bit_notand(Signmask(as(a)), a));
  }
}

