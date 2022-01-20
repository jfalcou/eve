//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/swap_adjacent_groups.hpp>

namespace eve::detail
{
  template<typename T, typename N, std::ptrdiff_t G>
  EVE_FORCEINLINE
  wide<T, typename N::combined_type>
  deinterleave_groups_shuffle_(EVE_SUPPORTS(neon128_), wide<T, N> v0, wide<T, N> v1, fixed<G>)
    requires (G < N()) && arm_abi<abi_t<T, N>>
  {
    using w_t = wide<T, N>;
    using r_t = wide<T, typename N::combined_type>;

    constexpr auto c = categorize<w_t>();

    static_assert (sizeof(T) * G <= 8, "only aggregation above anyways");

    if constexpr (G > 1)
    {
      using up_t = upgrade_t<T>;
      auto const up0 = bit_cast(v0, as<wide<up_t,typename N::split_type>>());
      auto const up1 = bit_cast(v1, as<wide<up_t,typename N::split_type>>());
      return bit_cast(deinterleave_groups_shuffle(up0, up1, fixed<G/2>{}), as<r_t>{});
    }
    // res represented by 8 bytes
    else if constexpr ( N() == 2 && sizeof(T) * N() < 8 && current_api >= asimd )
    {
           if constexpr ( c == category::int16x4  ) return vzip1_s16(v0, v1);
      else if constexpr ( c == category::uint16x4 ) return vzip1_u16(v0, v1);
      else if constexpr ( c == category::int8x8   ) return vzip1_s8 (v0, v1);
      else if constexpr ( c == category::uint8x8  ) return vzip1_u8 (v0, v1);
    }
    else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v0, v1, eve::lane<G>);
  }
}
