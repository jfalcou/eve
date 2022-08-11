//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
                max_(EVE_SUPPORTS(neon128_),
                     wide<T, N> const                &v0,
                     wide<T, N> const                &v1) noexcept requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if constexpr( cat == category::int32x4 ) return vmaxq_s32(v0, v1);
  else if constexpr( cat == category::int16x8 ) return vmaxq_s16(v0, v1);
  else if constexpr( cat == category::int8x16 ) return vmaxq_s8(v0, v1);
  else if constexpr( cat == category::uint32x4 ) return vmaxq_u32(v0, v1);
  else if constexpr( cat == category::uint16x8 ) return vmaxq_u16(v0, v1);
  else if constexpr( cat == category::uint8x16 ) return vmaxq_u8(v0, v1);
  else if constexpr( cat == category::float32x4 ) return vmaxq_f32(v0, v1);
  else if constexpr( cat == category::int32x2 ) return vmax_s32(v0, v1);
  else if constexpr( cat == category::int16x4 ) return vmax_s16(v0, v1);
  else if constexpr( cat == category::int8x8 ) return vmax_s8(v0, v1);
  else if constexpr( cat == category::uint32x2 ) return vmax_u32(v0, v1);
  else if constexpr( cat == category::uint16x4 ) return vmax_u16(v0, v1);
  else if constexpr( cat == category::uint8x8 ) return vmax_u8(v0, v1);
  else if constexpr( cat == category::float32x2 ) return vmax_f32(v0, v1);
  else if constexpr( current_api >= asimd )
  {
    if constexpr( cat == category::float64x1 ) return vmax_f64(v0, v1);
    else if constexpr( cat == category::float64x2 ) return vmaxq_f64(v0, v1);
    else if constexpr( sizeof(T) == 8 ) return map(max, v0, v1);
  }
  else if constexpr( sizeof(T) == 8 ) return map(max, v0, v1);
}
}
