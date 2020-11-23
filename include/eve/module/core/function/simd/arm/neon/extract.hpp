//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template<typename T, typename N, typename I, auto V, arm_abi ABI>
  EVE_FORCEINLINE logical<T> extract_(EVE_SUPPORTS(neon128_),
                                      logical<wide<T, N, ABI>> const &v0,
                                      std::integral_constant<I, V> const &u) noexcept
  {
    return logical<T>(extract(v0.bits(), u));
  }

  template<typename T, typename N, typename I, auto V, arm_abi ABI>
  EVE_FORCEINLINE T extract_(EVE_SUPPORTS(neon128_),
                                      logical<wide<T, N, ABI>> const &v0,
                                      std::integral_constant<I, V> const &) noexcept
                             std::integral_constant<I, V> const &) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

          if constexpr( cat == category::int32x4  ) return vget_laneq_s32(v0, V);
    else  if constexpr( cat == category::int16x8  ) return vget_laneq_s16(v0, V);
    else  if constexpr( cat == category::int8x16  ) return vget_laneq_s8(v0, V);
    else  if constexpr( cat == category::int32x2  ) return vget_lane_s32(v0, V);
    else  if constexpr( cat == category::int16x4  ) return vget_lane_s16(v0, V);
    else  if constexpr( cat == category::int8x8   ) return vget_lane_s8(v0, V);
    else  if constexpr( cat == category::int32x4  ) return vget_laneq_u32(v0, V);
    else  if constexpr( cat == category::int16x8  ) return vget_laneq_u16(v0, V);
    else  if constexpr( cat == category::int8x16  ) return vget_laneq_u8(v0, V);
    else  if constexpr( cat == category::int32x2  ) return vget_lane_u32(v0, V);
    else  if constexpr( cat == category::int16x4  ) return vget_lane_u16(v0, V);
    else  if constexpr( cat == category::int8x8   ) return vget_lane_u8(v0, V);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x1) return vget_lane_f64(v0, V);
    else  if constexpr( cat == category::float32x2) return vget_lane_f32(v0, V);
    else  if constexpr( cat == category::float64x2) return vget_laneq_f64(v0, V);
    else  if constexpr( cat == category::float32x4) return vget_laneq_f32(v0, V);
#endif
  }
}
