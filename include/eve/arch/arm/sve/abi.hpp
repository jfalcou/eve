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
  extern arm_sve_128_ hardware_abi_of<T,Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( spy::simd_instruction_set.width == 256 )
  extern arm_sve_256_ hardware_abi_of<T,Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( spy::simd_instruction_set.width == 512 )
  extern arm_sve_512_ hardware_abi_of<T,Cardinal>;
}
