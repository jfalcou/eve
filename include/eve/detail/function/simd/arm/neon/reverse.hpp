//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/swap_adjacent_groups.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N> reverse_( EVE_SUPPORTS(neon128_), wide<T,N> v) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr bool one_instruction_basic_swizzle = (current_api >= asimd) || std::same_as<abi_t<T, N>, arm_64_>;

    // two reverse instructions seem better than one table lookup.
    if constexpr ( N() >= 8 && one_instruction_basic_swizzle) return reverse_(EVE_RETARGET(cpu_), v);
    else
    {
      if constexpr ( N() >= 16 ) v = eve::swap_adjacent_groups(v, lane<8>);
      if constexpr ( N() >= 8  ) v = eve::swap_adjacent_groups(v, lane<4>);
      if constexpr ( N() >= 4  ) v = eve::swap_adjacent_groups(v, lane<2>);
      if constexpr ( N() >= 2  ) v = eve::swap_adjacent_groups(v, lane<1>);
      return v;
    }
  }
}
