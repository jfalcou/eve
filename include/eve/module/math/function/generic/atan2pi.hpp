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
#include <eve/function/radinpi.hpp>

namespace eve::detail
{
  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto atan2pi_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  {
    return arithmetic_call(atan2pi, a, b);
  }

  template<floating_real_value T, floating_real_value U>
  EVE_FORCEINLINE auto
  atan2pi_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b) noexcept
  {
    return arithmetic_call(pedantic_(atan2pi), a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto atan2pi_(EVE_SUPPORTS(cpu_), T const &a, T const &b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return radinpi(atan2(a, b));
    else
      return apply_over(atan2pi, a, b);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto
  atan2pi_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, T const &b) noexcept
  {
    if constexpr( has_native_abi_v<T> )
      return radinpi(pedantic_(atan2)(a, b));
    else
      return apply_over(pedantic_(atan2pi), a, b);
  }
}

