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
#include <bit>
#include <optional>

namespace eve
{
  EVE_MAKE_CALLABLE(broadcast_group_, broadcast_group);

  //================================================================================================
  // Classify a pattern as a bcstg
  namespace detail
  {
    // Find the proper broadcast group shape. IF none is found, returns {-1,-1}
    template<std::size_t Cardinal,std::size_t Size>
    constexpr inline auto find_broadcast_group(std::array<std::ptrdiff_t,Size> const& pattern)
    {
      struct bg { std::ptrdiff_t group = -1, index = -1; };

      for(std::ptrdiff_t g = Cardinal;g > 0;g /= 2)
      {
        std::ptrdiff_t nb_idx = Cardinal/g;

        for(std::ptrdiff_t idx = 0;idx < nb_idx;idx++)
        {
          // Compute what we expect
          std::array<std::ptrdiff_t,Size> expected;
          for(std::size_t i=0;i<Size;++i) expected[i] = idx*g+(i%g);

          // Is it what we want ?
          if( pattern == expected ) return bg{g,idx};
        }
      }

      return bg{};
    }
  }

  // Compute the expected broadcast group if any
  template<std::ptrdiff_t Sz, std::ptrdiff_t... Is> inline constexpr auto is_broadcast_group = []()
  {
    constexpr std::array<std::ptrdiff_t,sizeof...(Is)> p = {Is...};
    constexpr auto result = detail::find_broadcast_group<Sz>(p);

    if constexpr( result.group != -1 )
      return std::optional{ std::pair{ lane<result.group>, index<result.index>} };
    else
      return std::optional<int>{};
  }();
}

#include <eve/detail/function/simd/common/broadcast_group.hpp>
