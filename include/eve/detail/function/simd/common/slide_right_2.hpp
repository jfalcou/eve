//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/slide_right.hpp>
#include <eve/function/combine.hpp>

namespace eve::detail
{
  template <simd_value Wide, std::ptrdiff_t Shift>
  EVE_FORCEINLINE Wide slide_right_2_(EVE_SUPPORTS(cpu_), Wide x, Wide y, index_t<Shift>) noexcept
  requires(Shift <= Wide::size() )
  {
         if constexpr ( Shift == 0                 ) return y;
    else if constexpr ( Shift == Wide::size()      ) return x;
    else if constexpr ( has_aggregated_abi_v<Wide> )
    {
      // [aa bb] [cc dd] => [bccd], [abbc]
      auto [aa, bb] = x.slice();
      auto [cc, dd] = y.slice();

      constexpr std::ptrdiff_t half = Wide::size() / 2;

      if constexpr ( Shift <= half ) // [bccd]
      {
        auto s = index<Shift>;
        return Wide{ slide_right_2(bb, cc, s), slide_right_2(cc, dd, s) };
      }
      else
      {
        auto s = index<Shift - half>;
        return Wide{ slide_right_2(aa, bb, s), slide_right_2(bb, cc, s) };
      }
    }
    else if constexpr ( !native_simd_for_abi<Wide, typename Wide::abi_type> )
    {
      return slide_right( eve::combine(x, y), index<Shift>).slice(upper_);
    }
    else
    {
      Wide res{ [&](int i, int size) {
        if (i < Shift) return x.get(size - Shift + i);
        else           return y.get(i - Shift);
      }};
      return res;
    }
  }
}
