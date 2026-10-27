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
  extern arm_64_ hardware_abi_of<T,Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( width_in_bits<T,Cardinal> == 128 )
  extern arm_128_ hardware_abi_of<T,Cardinal>;

  template<typename T>
  requires ( spy::simd_instruction_set != spy::asimd_ && (std::same_as<T, double> || std::same_as<T, eve::float16_t>))
  inline constexpr bool should_emulate_v<T> = true;
}
