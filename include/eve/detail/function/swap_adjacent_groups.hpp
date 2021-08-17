//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/pattern.hpp>
#include <eve/detail/kumi.hpp>
#include <bit>

namespace eve
{
  EVE_MAKE_CALLABLE(swap_adjacent_groups_, swap_adjacent_groups);

  namespace detail
  {
    //==============================================================================================
    // Classify a pattern as a swag
    template<std::ptrdiff_t G, std::ptrdiff_t N>
    inline constexpr
    auto swap_adjacent_groups_pattern = fix_pattern<N>( [](auto i, auto)
                                                      {
                                                        if(G!=N)
                                                          return (i+G)%(G*2) + (G*2)*(i/(G*2));
                                                        else
                                                          return i;
                                                      }
                                                    );

    template<std::ptrdiff_t... I> inline constexpr auto is_swag = []()
    {
      // List all possible swags for a current size
      constexpr auto sz = sizeof...(I);
      constexpr auto x = []<std::size_t... N>( std::index_sequence<N...> )
      {
        return kumi::make_tuple(swap_adjacent_groups_pattern<sz/(1<<(N+1)),sz>... );
      }(std::make_index_sequence<std::bit_width(sz)-1>{});

      // Find the fitting one
      constexpr auto idx = detail::find_index(pattern<I...>,x);
      return fixed<sz/(1<<(idx+1))>{};
    }();
  }
}

#include <eve/detail/function/simd/common/swap_adjacent_groups.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/detail/function/simd/x86/swap_adjacent_groups.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/detail/function/simd/arm/neon/swap_adjacent_groups.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/detail/function/simd/ppc/swap_adjacent_groups.hpp>
#endif
