//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/pattern.hpp>

namespace eve::detail
{
template<real_scalar_value T, typename N, std::ptrdiff_t G>
    EVE_FORCEINLINE wide<T, N>
                    swap_adjacent_groups_(EVE_SUPPORTS(neon128_), wide<T, N> v, fixed<G>) noexcept
    requires(G <= N::value)
    && arm_abi<abi_t<T, N>>
{
  using that_t = wide<T, N>;

  if constexpr( G == N::value ) { return v; }
  else
  {
    constexpr auto c = categorize<that_t>();

    if constexpr( G == 1 )
    {
      if constexpr( c == category::int64x2 ) return vextq_s64(v, v, 1);
      else if constexpr( c == category::uint64x2 ) return vextq_u64(v, v, 1);
      else if constexpr( c == category::float64x1 ) return v;
      else if constexpr( c == category::int64x1 ) return v;
      else if constexpr( c == category::uint64x1 ) return v;
      else if constexpr( c == category::float32x4 ) return vrev64q_f32(v);
      else if constexpr( c == category::int32x4 ) return vrev64q_s32(v);
      else if constexpr( c == category::uint32x4 ) return vrev64q_u32(v);
      else if constexpr( c == category::float32x2 ) return vrev64_f32(v);
      else if constexpr( c == category::int32x2 ) return vrev64_s32(v);
      else if constexpr( c == category::uint32x2 ) return vrev64_u32(v);
      else if constexpr( c == category::int16x8 ) return vrev32q_s16(v);
      else if constexpr( c == category::uint16x8 ) return vrev32q_u16(v);
      else if constexpr( c == category::int16x4 ) return vrev32_s16(v);
      else if constexpr( c == category::uint16x4 ) return vrev32_u16(v);
      else if constexpr( c == category::int8x16 ) return vrev16q_s8(v);
      else if constexpr( c == category::uint8x16 ) return vrev16q_u8(v);
      else if constexpr( c == category::int8x8 ) return vrev16_s8(v);
      else if constexpr( c == category::uint8x8 ) return vrev16_u8(v);
      else if constexpr( c == category::float64x2 )
      {
        if constexpr( current_api >= asimd ) return vextq_f64(v, v, 1);
        else return that_t(v.get(1), v.get(0));
      }
    }
    else
    {
      using up_t    = upgrade_t<T>;
      auto const up = bit_cast(v, as<wide<up_t, typename N::split_type>>());
      return bit_cast(swap_adjacent_groups(up, fixed<G / 2> {}), as(v));
    }
  }
}
}
