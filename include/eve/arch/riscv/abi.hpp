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
  requires ( spy::simd_instruction_set.width >= 64)
  inline constexpr auto hardware_abi_of<T,Cardinal> = riscv_{};

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( width_in_bits<T,Cardinal> > riscv_::bits )
  inline constexpr bool should_aggregate_v<T, Cardinal> = true;
}
