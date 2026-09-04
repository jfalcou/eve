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
  requires ( spy::simd_instruction_set.width == 128 )
  inline constexpr auto hardware_abi_of<T,Cardinal> = arm_sve_128_{};

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( spy::simd_instruction_set.width == 256 )   
  inline constexpr auto hardware_abi_of<T,Cardinal> = arm_sve_256_{};

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( spy::simd_instruction_set.width == 512 )   
  inline constexpr auto hardware_abi_of<T,Cardinal> = arm_sve_512_{};
}
