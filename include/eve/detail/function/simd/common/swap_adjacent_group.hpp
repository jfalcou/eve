//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<simd_value Wide, std::ptrdiff_t G>
  EVE_FORCEINLINE auto swap_adjacent_group_(EVE_SUPPORTS(cpu_), Wide v, fixed<G>) noexcept
  requires(G <= Wide::size() )
  {
    if constexpr(G == Wide::size())
    {
      return v;
    }
    else if constexpr( has_aggregated_abi_v<Wide> )
    {
      if constexpr(G == Wide::size()/2)
      {
        auto[l,h] = v.slice();
        return Wide{h,l};
      }
      else
      {
        auto[l,h] = v.slice();
        return Wide {swap_adjacent_group(l,fixed<G>{}),swap_adjacent_group(h,fixed<G>{})};
      }
    }
    else
    {
      // In this case, we don't have anything special to do so we just swizzle
      return v[eve::swap_adjacent_group_n<G,Wide::size()>];
    }
  }

  template<simd_value Wide, std::ptrdiff_t G>
  EVE_FORCEINLINE auto swap_adjacent_group_(EVE_SUPPORTS(cpu_), logical<Wide> v, fixed<G> f) noexcept
  requires(G <= Wide::size() )
  {
    return bit_cast( swap_adjacent_group(v.mask(),f), as(v));
  }
}
