//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/swap_adjacent_groups.hpp>

#include <eve/detail/function/simd/arm/neon/neon_struct_to_wide.hpp>

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

    // no way to shuffle 8 bytes on arm-v7 other than slice and combine
    if constexpr ( sizeof(T) * G == 8 && current_api < asimd )
    {
      return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v0, v1, eve::lane<G>);
    }
    else if constexpr ( G > 1 )
    {
      using up_t = upgrade_t<T>;
      auto const up0 = bit_cast(v0, as<wide<up_t,typename N::split_type>>());
      auto const up1 = bit_cast(v1, as<wide<up_t,typename N::split_type>>());
      return bit_cast(deinterleave_groups_shuffle(up0, up1, fixed<G/2>{}), as<r_t>{});
    }
    // ===================================================================================================
    // The equivalent family of intrinsics on arm is uzp.
    // However, for smaller than 8 bytes we need to make do with others because of zeroes in the top bytes
    // ===================================================================================================
    // sizeof(T) == 8, at least asimd ================================
    else if constexpr ( c == category::float64x2 ) return {w_t{vuzp1q_f64(v0, v1)}, w_t{vuzp2q_f64(v0, v1)}};
    else if constexpr ( c == category::int64x2   ) return {w_t{vuzp1q_s64(v0, v1)}, w_t{vuzp2q_s64(v0, v1)}};
    else if constexpr ( c == category::uint64x2  ) return {w_t{vuzp1q_u64(v0, v1)}, w_t{vuzp2q_u64(v0, v1)}};
    // sizeof(T) == 4 ==============================================
    else if constexpr ( c == category::float32x2 ) return neon_struct_to_wide(vuzp_f32 (v0, v1));
    else if constexpr ( c == category::int32x2   ) return neon_struct_to_wide(vuzp_s32 (v0, v1));
    else if constexpr ( c == category::uint32x2  ) return neon_struct_to_wide(vuzp_u32 (v0, v1));
    else if constexpr ( c == category::float32x4 ) return neon_struct_to_wide(vuzpq_f32 (v0, v1));
    else if constexpr ( c == category::int32x4   ) return neon_struct_to_wide(vuzpq_s32(v0, v1));
    else if constexpr ( c == category::uint32x4  ) return neon_struct_to_wide(vuzpq_u32(v0, v1));
    // sizeof(T) == 2 ==============================================
    else if constexpr ( c == category::int16x4  && N() == 2 && current_api >= asimd ) return vzip1_s16(v0, v1);
    else if constexpr ( c == category::uint16x4 && N() == 2 && current_api >= asimd ) return vzip1_u16(v0, v1);
    else if constexpr ( c == category::int16x4  && N() == 2                         ) return vzip_s16 (v0, v1).val[0];
    else if constexpr ( c == category::uint16x4 && N() == 2                         ) return vzip_u16 (v0, v1).val[0];
    else if constexpr ( c == category::int16x4                                      ) return neon_struct_to_wide(vuzp_s16 (v0, v1));
    else if constexpr ( c == category::uint16x4                                     ) return neon_struct_to_wide(vuzp_u16 (v0, v1));
    else if constexpr ( c == category::int16x8                                      ) return neon_struct_to_wide(vuzpq_s16(v0, v1));
    else if constexpr ( c == category::uint16x8                                     ) return neon_struct_to_wide(vuzpq_u16(v0, v1));
    // sizeof(T) == 1 ==============================================
    else if constexpr ( c == category::int8x8   && N() == 2 && current_api >= asimd ) return vzip1_s8  (v0, v1);
    else if constexpr ( c == category::uint8x8  && N() == 2 && current_api >= asimd ) return vzip1_u8  (v0, v1);
    else if constexpr ( c == category::int8x8   && N() == 2                         ) return vzip_s8   (v0, v1).val[0];
    else if constexpr ( c == category::uint8x8  && N() == 2                         ) return vzip_u8   (v0, v1).val[0];
    else if constexpr ( c == category::int8x8   && N() == 8                         ) return neon_struct_to_wide(vuzp_s8 (v0, v1));
    else if constexpr ( c == category::uint8x8  && N() == 8                         ) return neon_struct_to_wide(vuzp_u8 (v0, v1));
    else if constexpr ( c == category::int8x16                                      ) return neon_struct_to_wide(vuzpq_s8(v0, v1));
    else if constexpr ( c == category::uint8x16                                     ) return neon_struct_to_wide(vuzpq_u8(v0, v1));
    else return deinterleave_groups_shuffle_(EVE_RETARGET(cpu_), v0, v1, eve::lane<G>);
  }
}
