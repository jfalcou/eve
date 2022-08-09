//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
                bit_andnot_(EVE_SUPPORTS(neon128_),
                            wide<T, N> const                &v0,
                            wide<T, N> const                &v1) noexcept requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( cat == category::float32x4 )
    return vreinterpretq_f32_u32(vbicq_u32(vreinterpretq_u32_f32(v0), vreinterpretq_u32_f32(v1)));
  else if constexpr( cat == category::float32x2 )
    return vreinterpret_f32_u32(vbic_u32(vreinterpret_u32_f32(v0), vreinterpret_u32_f32(v1)));
  else if constexpr( cat == category::int64x1 ) return vbic_s64(v0, v1);
  else if constexpr( cat == category::int32x2 ) return vbic_s32(v0, v1);
  else if constexpr( cat == category::int16x4 ) return vbic_s16(v0, v1);
  else if constexpr( cat == category::int8x8 ) return vbic_s8(v0, v1);
  else if constexpr( cat == category::uint64x1 ) return vbic_u64(v0, v1);
  else if constexpr( cat == category::uint32x2 ) return vbic_u32(v0, v1);
  else if constexpr( cat == category::uint16x4 ) return vbic_u16(v0, v1);
  else if constexpr( cat == category::uint8x8 ) return vbic_u8(v0, v1);
  else if constexpr( cat == category::int64x2 ) return vbicq_s64(v0, v1);
  else if constexpr( cat == category::int32x4 ) return vbicq_s32(v0, v1);
  else if constexpr( cat == category::int16x8 ) return vbicq_s16(v0, v1);
  else if constexpr( cat == category::int8x16 ) return vbicq_s8(v0, v1);
  else if constexpr( cat == category::uint64x2 ) return vbicq_u64(v0, v1);
  else if constexpr( cat == category::uint32x4 ) return vbicq_u32(v0, v1);
  else if constexpr( cat == category::uint16x8 ) return vbicq_u16(v0, v1);
  else if constexpr( cat == category::uint8x16 ) return vbicq_u8(v0, v1);
  else if constexpr( current_api >= asimd )
  {
    if constexpr( cat == category::float64x1 )
      return vreinterpret_f64_u64(vbic_u64(vreinterpret_u64_f64(v0), vreinterpret_u64_f64(v1)));
    else if constexpr( cat == category::float64x2 )
      return vreinterpretq_f64_u64(vbicq_u64(vreinterpretq_u64_f64(v0), vreinterpretq_u64_f64(v1)));
  }
}
}
