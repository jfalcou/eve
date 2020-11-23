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
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<typename T, typename N, arm_abi ABI>
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_less_(EVE_SUPPORTS(neon128_),
                                                    wide<T, N, ABI> const &v0,
                                                    wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

    if constexpr( cat == category::int32x4  ) return vcltq_s32(v0, v1);
    else  if constexpr( cat == category::int16x8  ) return vcltq_s16(v0, v1);
    else  if constexpr( cat == category::int8x16  ) return vcltq_s8(v0, v1);
    else  if constexpr( cat == category::uint32x4 ) return vcltq_u32(v0, v1);
    else  if constexpr( cat == category::uint16x8 ) return vcltq_u16(v0, v1);
    else  if constexpr( cat == category::uint8x16 ) return vcltq_u8(v0, v1);
    else  if constexpr( cat == category::float32x4) return vcltq_f32(v0, v1);
    else  if constexpr( cat == category::int32x2  ) return vclt_s32(v0, v1);
    else  if constexpr( cat == category::int16x4  ) return vclt_s16(v0, v1);
    else  if constexpr( cat == category::int8x8   ) return vclt_s8(v0, v1);
    else  if constexpr( cat == category::uint32x2 ) return vclt_u32(v0, v1);
    else  if constexpr( cat == category::uint16x4 ) return vclt_u16(v0, v1);
    else  if constexpr( cat == category::uint8x8  ) return vclt_u8(v0, v1);
    else  if constexpr( cat == category::float32x2) return vclt_f32(v0, v1);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x1) return vclt_f64(v0, v1);
    else  if constexpr( cat == category::int64x1)   return vclt_s64(v0, v1);
    else  if constexpr( cat == category::uint64x1)  return vclt_u64(v0, v1);
    else  if constexpr( cat == category::float64x2) return vcltq_f64(v0, v1);
    else  if constexpr( cat == category::int64x2)   return vcltq_s64(v0, v1);
    else  if constexpr( cat == category::uint64x2)  return vcltq_u64(v0, v1);
#else
    else  if constexpr( sizeof(T) == 8 )            return map(is_less, v0, v1);
#endif
  }
}
