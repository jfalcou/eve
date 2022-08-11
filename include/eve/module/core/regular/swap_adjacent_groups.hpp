//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/pattern.hpp>

namespace eve
{
EVE_MAKE_CALLABLE(swap_adjacent_groups_, swap_adjacent_groups);

template<std::ptrdiff_t G, std::ptrdiff_t N>
inline constexpr auto swap_adjacent_groups_pattern = fix_pattern<N>(
    [](auto i, auto)
    {
      if( G != N ) return (i + G) % (G * 2) + (G * 2) * (i / (G * 2));
      else return i;
    });
}

#include <eve/module/core/regular/impl/swap_adjacent_groups.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/swap_adjacent_groups.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/swap_adjacent_groups.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/swap_adjacent_groups.hpp>
#endif
