//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/max.hpp>
#include <eve/function/sub.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // regular case
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto fdim_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires compatible_values<T, U>
  {
    return arithmetic_call(fdim, a, b);
  }

  template<real_value T>
  EVE_FORCEINLINE auto fdim_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    auto r = if_else(a >= b, sub(a, b), eve::zero);
    return r;
  }
}
