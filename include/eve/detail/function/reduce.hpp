//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/vectorized.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/regular/swap_adjacent_groups.hpp>
#include <bit>

namespace eve::detail
{
  //================================================================================================
  // reduce toward wide using a generic butterfly algorithm
  template<simd_value Wide, typename Callable>
  EVE_FORCEINLINE auto butterfly_reduction(Wide v, Callable f) noexcept
  {
    if constexpr( Wide::size() == 1 )
    {
      return v;
    }
    else
    {
      constexpr auto depth = std::bit_width(std::size_t{Wide::size()}) - 1;

      return [&]<std::size_t... I>(std::index_sequence<I...>) mutable
      {
        ((v = f(v,swap_adjacent_groups(v, fixed<(1<<I)>{} ))),...);
        return v;
      }(std::make_index_sequence<depth>{});
    }
  }
}
