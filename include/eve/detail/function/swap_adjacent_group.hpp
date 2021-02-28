//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/pattern.hpp>

namespace eve
{
  EVE_MAKE_CALLABLE(swap_adjacent_group_, swap_adjacent_group);

  //================================================================================================
  // Premade pattern generator
  template<std::ptrdiff_t G, std::ptrdiff_t N>
  inline constexpr auto swap_adjacent_group_n = fix_pattern<N>( [](auto i, auto)
                                                                {
                                                                  if(G!=N)
                                                                  {
                                                                    auto sub = G*2;
                                                                    return (i+G)%sub + sub*(i/sub);
                                                                  }
                                                                  else
                                                                  {
                                                                    return i;
                                                                  }
                                                                }
                                                              );
}

#include <eve/detail/function/simd/common/swap_adjacent_group.hpp>

#if defined(EVE_HW_X86)
#  include <eve/detail/function/simd/x86/swap_adjacent_group.hpp>
#endif

#if defined(EVE_HW_ARM)
#  include <eve/detail/function/simd/arm/neon/swap_adjacent_group.hpp>
#endif

#if defined(EVE_HW_POWERPC)
#  include <eve/detail/function/simd/ppc/swap_adjacent_group.hpp>
#endif
