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
  template<typename T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> min_(EVE_SUPPORTS(neon128_),
                                       wide<T, N, ABI> const &v0,
                                       wide<T, N, ABI> const &v1) noexcept
  {
    constexpr auto cat = categorize<wide<T, N, ABI>>();

          if constexpr( cat == category::int32x4  ) return vminq_s32(v0, v1);
    else  if constexpr( cat == category::int16x8  ) return vminq_s16(v0, v1);
    else  if constexpr( cat == category::int8x16  ) return vminq_s8(v0, v1);
    else  if constexpr( cat == category::uint32x4 ) return vminq_u32(v0, v1);
    else  if constexpr( cat == category::uint16x8 ) return vminq_u16(v0, v1);
    else  if constexpr( cat == category::uint8x16 ) return vminq_u8(v0, v1);
    else  if constexpr( cat == category::float32x4) return vminq_f32(v0, v1);
    else  if constexpr( cat == category::int32x2  ) return vmin_s32(v0, v1);
    else  if constexpr( cat == category::int16x4  ) return vmin_s16(v0, v1);
    else  if constexpr( cat == category::int8x8   ) return vmin_s8(v0, v1);
    else  if constexpr( cat == category::uint32x2 ) return vmin_u32(v0, v1);
    else  if constexpr( cat == category::uint16x4 ) return vmin_u16(v0, v1);
    else  if constexpr( cat == category::uint8x8  ) return vmin_u8(v0, v1);
    else  if constexpr( cat == category::float32x2) return vmin_f32(v0, v1);
#if defined(__aarch64__)
    else  if constexpr( cat == category::float64x1) return vmin_f64(v0, v1);
    else  if constexpr( cat == category::float64x2) return vminq_f64(v0, v1);
#endif
    else  if constexpr( sizeof(T) == 8 )            return map(min, v0, v1);
  }

  template<typename T, typename N, arm_abi ABI>
  EVE_FORCEINLINE wide<T, N, ABI> min_( EVE_SUPPORTS(neon128_)
                                      , pedantic_type const &
                                      , wide<T, N, ABI> const &a0
                                      , wide<T, N, ABI> const &a1
                                      ) noexcept
  {
    auto tmp = eve::min(a0, a1);
    if constexpr(eve::platform::supports_invalids) tmp = if_else(is_nan(a1), a0, tmp);
    return if_else(is_eqz(a0) && is_eqz(a1), bit_or(a0, a1), tmp);
  }
}
