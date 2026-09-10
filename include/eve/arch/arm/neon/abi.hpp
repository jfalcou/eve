//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/cpu/abi.hpp>

namespace eve::_
{
  template<typename T, std::ptrdiff_t Cardinal>
  requires ( width_in_bits<T,Cardinal> <= 64 )
  inline constexpr auto hardware_abi_of<T,Cardinal> = arm_64_{};

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( width_in_bits<T,Cardinal> == 128 )
  inline constexpr auto hardware_abi_of<T,Cardinal> = arm_128_{};

  template<typename T>
  requires ( spy::simd_instruction_set != spy::asimd_ && (std::same_as<T, double> || std::same_as<T, eve::float16_t>))
  inline constexpr bool should_emulate_v<T> = true;
}
