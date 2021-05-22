//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once


#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>

#include <eve/detail/function/swizzle.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
  template<simd_value Wide>
  EVE_FORCEINLINE Wide reverse_(EVE_SUPPORTS(cpu_), Wide const& v)
  {
    if constexpr ( has_aggregated_abi_v<Wide> ) {
      auto [l, h] = v.slice();
      l = eve::reverse(l);
      h = eve::reverse(h);
      return Wide{h, l};
    }
    else
    {
      return basic_swizzle(v, eve::fix_pattern<Wide::size()>([](int i, int size) { return size - i - 1; }));
    }
  }

  template<simd_value Wide, std::ptrdiff_t N>
  EVE_FORCEINLINE logical<Wide> reverse_(EVE_SUPPORTS(cpu_), logical<Wide> const& v)
  {
    using abi_t = typename Wide::abi_type;
    if constexpr ( !abi_t::is_wide_logical )
    {
      // Reconstruct mask, reverse then turn to mask again
      auto const m = v.mask();
      auto const res = eve::reverse(m);
      return to_logical(res);
    }
    else
    {
      return bit_cast( reverse(v.bits()), as(v) );
    }
  }
}
