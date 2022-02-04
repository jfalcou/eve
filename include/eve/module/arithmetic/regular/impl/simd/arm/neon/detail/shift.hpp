//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<integral_real_scalar_value T, typename N, typename I>
  EVE_FORCEINLINE wide<T, N> neon_shifter(wide<T, N> v0, wide<I, N> v1) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, signed>, N>;
    auto s1 = bit_cast(v1, as<i_t>());

    constexpr auto c = categorize<wide<T, N>>();

    // arm_128
         if constexpr ( c == category::int64x2  ) return vshlq_s64(v0, s1);
    else if constexpr ( c == category::uint64x2 ) return vshlq_u64(v0, s1);
    else if constexpr ( c == category::int32x4  ) return vshlq_s32(v0, s1);
    else if constexpr ( c == category::uint32x4 ) return vshlq_u32(v0, s1);
    else if constexpr ( c == category::int16x8  ) return vshlq_s16(v0, s1);
    else if constexpr ( c == category::uint16x8 ) return vshlq_u16(v0, s1);
    else if constexpr ( c == category::int8x16  ) return vshlq_s8 (v0, s1);
    else if constexpr ( c == category::uint8x16 ) return vshlq_u8 (v0, s1);
    // arm_64
    else if constexpr ( c == category::int64x1  ) return vshl_s64 (v0, s1);
    else if constexpr ( c == category::uint64x1 ) return vshl_u64 (v0, s1);
    else if constexpr ( c == category::int32x2  ) return vshl_s32 (v0, s1);
    else if constexpr ( c == category::uint32x2 ) return vshl_u32 (v0, s1);
    else if constexpr ( c == category::int16x4  ) return vshl_s16 (v0, s1);
    else if constexpr ( c == category::uint16x4 ) return vshl_u16 (v0, s1);
    else if constexpr ( c == category::int8x8   ) return vshl_s8  (v0, s1);
    else if constexpr ( c == category::uint8x8  ) return vshl_u8  (v0, s1);
  }
}
