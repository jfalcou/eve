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
  requires (  (spy::simd_instruction_set >= spy::vsx_ || spy::simd_instruction_set >= spy::vmx_) 
              && width_in_bits<T,Cardinal> <= 128)
  inline constexpr auto hardware_abi_of<T,Cardinal> = ppc_{};

  template<typename T>
  requires( spy::simd_instruction_set >= spy::vmx_ && spy::simd_instruction_set < spy::vsx_ && std::same_as<T, double>)
  inline constexpr bool should_emulate_v<T> = true;
}
