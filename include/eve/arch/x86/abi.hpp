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
  requires ( spy::simd_instruction_set == spy::avx512_
            && !std::same_as<eve::current_api_type, eve::avx2_>
            && width_in_bits<T,Cardinal> == 512 )
  extern x86_512_ hardware_abi_of<T,Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( spy::simd_instruction_set >= spy::avx_ && width_in_bits<T,Cardinal> == 256 )
  extern x86_256_ hardware_abi_of<T,Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  requires ( spy::simd_instruction_set >= spy::sse1_ && width_in_bits<T,Cardinal> <= 128 )
  extern x86_128_ hardware_abi_of<T,Cardinal>;

  template<typename T, std::ptrdiff_t Cardinal>
  requires( spy::simd_instruction_set == spy::avx512_ && std::same_as<eve::current_api_type, eve::avx2_> )
  inline constexpr bool should_aggregate_v<T,Cardinal> = (width_in_bits<T,Cardinal> > spy::avx2_.width );
}
