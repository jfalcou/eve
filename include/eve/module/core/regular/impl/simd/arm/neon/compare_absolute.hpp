//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/simd_cast.hpp>
#include <eve/module/core/regular/is_greater_equal.hpp>
#include <eve/module/core/regular/is_greater.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/is_less.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N, typename F>
  EVE_FORCEINLINE logical<wide<T, N>> compare_absolute_(EVE_REQUIRES(neon128_), O const& opts,
                                                        wide<T, N> v, wide<T, N> w, F f) noexcept
  requires (arm_abi<abi_t<T, N>>)
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(F{} == is_less_equal)
    {
      if constexpr( c == category::int64x1    ) return vcale_s64 (v, w);
      else if constexpr( c == category::int64x2    ) return vcaleq_s64(v, w);
      else if constexpr( c == category::uint64x1   ) return vcale_u64 (v, w);
      else if constexpr( c == category::uint64x2   ) return vcaleq_u64(v, w);
      else if constexpr( c == category::int32x2    ) return vcale_s32 (v, w);
      else if constexpr( c == category::int32x4    ) return vcaleq_s32(v, w);
      else if constexpr( c == category::uint32x2   ) return vcale_u32 (v, w);
      else if constexpr( c == category::uint32x4   ) return vcaleq_u32(v, w);
      else if constexpr( c == category::int16x4    ) return vcale_s16 (v, w);
      else if constexpr( c == category::int16x8    ) return vcaleq_s16(v, w);
      else if constexpr( c == category::uint16x4   ) return vcale_u16 (v, w);
      else if constexpr( c == category::uint16x8   ) return vcaleq_u16(v, w);
      else if constexpr( c == category::int8x8     ) return vcale_s8  (v, w);
      else if constexpr( c == category::int8x16    ) return vcaleq_s8 (v, w);
      else if constexpr( c == category::uint8x8    ) return vcale_u8  (v, w);
      else if constexpr( c == category::uint8x16   ) return vcaleq_u8 (v, w);
      else if constexpr( c == category::float32x2  ) return vcale_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcaleq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcale_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcaleq_f64 (v, w);
      }
    }
    else if constexpr(F{} ==  is_greater_equal)
    {
      if constexpr( c == category::int64x1    ) return vcage_s64 (v, w);
      else if constexpr( c == category::int64x2    ) return vcageq_s64(v, w);
      else if constexpr( c == category::uint64x1   ) return vcage_u64 (v, w);
      else if constexpr( c == category::uint64x2   ) return vcageq_u64(v, w);
      else if constexpr( c == category::int32x2    ) return vcage_s32 (v, w);
      else if constexpr( c == category::int32x4    ) return vcageq_s32(v, w);
      else if constexpr( c == category::uint32x2   ) return vcage_u32 (v, w);
      else if constexpr( c == category::uint32x4   ) return vcageq_u32(v, w);
      else if constexpr( c == category::int16x4    ) return vcage_s16 (v, w);
      else if constexpr( c == category::int16x8    ) return vcageq_s16(v, w);
      else if constexpr( c == category::uint16x4   ) return vcage_u16 (v, w);
      else if constexpr( c == category::uint16x8   ) return vcageq_u16(v, w);
      else if constexpr( c == category::int8x8     ) return vcage_s8  (v, w);
      else if constexpr( c == category::int8x16    ) return vcageq_s8 (v, w);
      else if constexpr( c == category::uint8x8    ) return vcage_u8  (v, w);
      else if constexpr( c == category::uint8x16   ) return vcageq_u8 (v, w);
      else if constexpr( c == category::float32x2  ) return vcage_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcageq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcage_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcageq_f64 (v, w);
      }
    }
    else if constexpr(F{} == is_less)
    {
      if constexpr( c == category::int64x1    ) return vcalt_s64 (v, w);
      else if constexpr( c == category::int64x2    ) return vcaltq_s64(v, w);
      else if constexpr( c == category::uint64x1   ) return vcalt_u64 (v, w);
      else if constexpr( c == category::uint64x2   ) return vcaltq_u64(v, w);
      else if constexpr( c == category::int32x2    ) return vcalt_s32 (v, w);
      else if constexpr( c == category::int32x4    ) return vcaltq_s32(v, w);
      else if constexpr( c == category::uint32x2   ) return vcalt_u32 (v, w);
      else if constexpr( c == category::uint32x4   ) return vcaltq_u32(v, w);
      else if constexpr( c == category::int16x4    ) return vcalt_s16 (v, w);
      else if constexpr( c == category::int16x8    ) return vcaltq_s16(v, w);
      else if constexpr( c == category::uint16x4   ) return vcalt_u16 (v, w);
      else if constexpr( c == category::uint16x8   ) return vcaltq_u16(v, w);
      else if constexpr( c == category::int8x8     ) return vcalt_s8  (v, w);
      else if constexpr( c == category::int8x16    ) return vcaltq_s8 (v, w);
      else if constexpr( c == category::uint8x8    ) return vcalt_u8  (v, w);
      else if constexpr( c == category::uint8x16   ) return vcaltq_u8 (v, w);
      else if constexpr( c == category::float32x2  ) return vcalt_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcaltq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcalt_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcaltq_f64 (v, w);
      }
    }
    else if constexpr(F{} == is_greater)
    {
      if constexpr( c == category::int64x1    ) return vcagt_s64 (v, w);
      else if constexpr( c == category::int64x2    ) return vcagtq_s64(v, w);
      else if constexpr( c == category::uint64x1   ) return vcagt_u64 (v, w);
      else if constexpr( c == category::uint64x2   ) return vcagtq_u64(v, w);
      else if constexpr( c == category::int32x2    ) return vcagt_s32 (v, w);
      else if constexpr( c == category::int32x4    ) return vcagtq_s32(v, w);
      else if constexpr( c == category::uint32x2   ) return vcagt_u32 (v, w);
      else if constexpr( c == category::uint32x4   ) return vcagtq_u32(v, w);
      else if constexpr( c == category::int16x4    ) return vcagt_s16 (v, w);
      else if constexpr( c == category::int16x8    ) return vcagtq_s16(v, w);
      else if constexpr( c == category::uint16x4   ) return vcagt_u16 (v, w);
      else if constexpr( c == category::uint16x8   ) return vcagtq_u16(v, w);
      else if constexpr( c == category::int8x8     ) return vcagt_s8  (v, w);
      else if constexpr( c == category::int8x16    ) return vcagtq_s8 (v, w);
      else if constexpr( c == category::uint8x8    ) return vcagt_u8  (v, w);
      else if constexpr( c == category::uint8x16   ) return vcagtq_u8 (v, w);
      else if constexpr( c == category::float32x2  ) return vcagt_f32 (v, w);
      else if constexpr( c == category::float32x4  ) return vcagtq_f32(v, w);
      else if constexpr( current_api >= asimd )
      {
        if constexpr( c == category::float64x1 ) return vcagt_f64  (v, w);
        else  if constexpr( c == category::float64x2 ) return vcagtq_f64 (v, w);
      }
    }
    else return compare_absolute.behavior(cpu_{}, v, w, f);
  }
}
