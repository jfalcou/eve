//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/pedantic/atan2.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/radindeg.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  atan2d_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
    -> decltype(arithmetic_call(pedantic(atan2d), a, b))
  {
    return arithmetic_call(pedantic(atan2d), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto
  atan2d_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, T const &b) noexcept
  requires  has_native_abi_v<T>
  {
    return radindeg(pedantic(atan2)(a, b));
  }

}
