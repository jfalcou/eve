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
  EVE_FORCEINLINE as_logical_t<wide<T, N>> is_equal_(EVE_SUPPORTS(neon128_),
                                                     wide<T, N, ABI> const &v0,
                                                     wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

    if constexpr( cat == category::int32x4  ) return vceqq_s32(v0, v1);
    else  if constexpr( cat == category::int16x8  ) return vceqq_s16(v0, v1);
    else  if constexpr( cat == category::int8x16  ) return vceqq_s8(v0, v1);
    else  if constexpr( cat == category::uint32x4 ) return vceqq_u32(v0, v1);
    else  if constexpr( cat == category::uint16x8 ) return vceqq_u16(v0, v1);
    else  if constexpr( cat == category::uint8x16 ) return vceqq_u8(v0, v1);
    else  if constexpr( cat == category::float32x4) return vceqq_f32(v0, v1);
    else  if constexpr( cat == category::int32x2  ) return vceq_s32(v0, v1);
    else  if constexpr( cat == category::int16x4  ) return vceq_s16(v0, v1);
    else  if constexpr( cat == category::int8x8   ) return vceq_s8(v0, v1);
    else  if constexpr( cat == category::uint32x2 ) return vceq_u32(v0, v1);
    else  if constexpr( cat == category::uint16x4 ) return vceq_u16(v0, v1);
    else  if constexpr( cat == category::uint8x8  ) return vceq_u8(v0, v1);
    else  if constexpr( cat == category::float32x2) return vceq_f32(v0, v1);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x1) return vceq_f64(v0, v1);
    else  if constexpr( cat == category::int64x1)   return vceq_s64(v0, v1);
    else  if constexpr( cat == category::uint64x1)  return vceq_u64(v0, v1);
    else  if constexpr( cat == category::float64x2) return vceqq_f64(v0, v1);
    else  if constexpr( cat == category::int64x2)   return vceqq_s64(v0, v1);
    else  if constexpr( cat == category::uint64x2)  return vceqq_u64(v0, v1);
#else
    else  if constexpr( sizeof(T) == 8 )            return map(is_equal, v0, v1);
#endif
  }
}
