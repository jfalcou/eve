//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<typename T, typename N>
EVE_FORCEINLINE wide<T, N>
                min_(EVE_SUPPORTS(neon128_),
                     wide<T, N> const                &v0,
                     wide<T, N> const                &v1) noexcept requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( cat == category::int32x4 ) return vminq_s32(v0, v1);
  else if constexpr( cat == category::int16x8 ) return vminq_s16(v0, v1);
  else if constexpr( cat == category::int8x16 ) return vminq_s8(v0, v1);
  else if constexpr( cat == category::uint32x4 ) return vminq_u32(v0, v1);
  else if constexpr( cat == category::uint16x8 ) return vminq_u16(v0, v1);
  else if constexpr( cat == category::uint8x16 ) return vminq_u8(v0, v1);
  else if constexpr( cat == category::float32x4 ) return vminq_f32(v0, v1);
  else if constexpr( cat == category::int32x2 ) return vmin_s32(v0, v1);
  else if constexpr( cat == category::int16x4 ) return vmin_s16(v0, v1);
  else if constexpr( cat == category::int8x8 ) return vmin_s8(v0, v1);
  else if constexpr( cat == category::uint32x2 ) return vmin_u32(v0, v1);
  else if constexpr( cat == category::uint16x4 ) return vmin_u16(v0, v1);
  else if constexpr( cat == category::uint8x8 ) return vmin_u8(v0, v1);
  else if constexpr( cat == category::float32x2 ) return vmin_f32(v0, v1);
  else if constexpr( current_api >= asimd )
  {
    if constexpr( cat == category::float64x1 ) return vmin_f64(v0, v1);
    else if constexpr( cat == category::float64x2 ) return vminq_f64(v0, v1);
    else if constexpr( sizeof(T) == 8 ) return map(min, v0, v1);
  }
  else if constexpr( sizeof(T) == 8 ) return map(min, v0, v1);
}
}
