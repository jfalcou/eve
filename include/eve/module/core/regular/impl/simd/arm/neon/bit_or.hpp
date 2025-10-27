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
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_or_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

          if constexpr( c == category::int64x1  ) return vorr_s64 (a, b);
    else  if constexpr( c == category::int32x2  ) return vorr_s32 (a, b);
    else  if constexpr( c == category::int16x4  ) return vorr_s16 (a, b);
    else  if constexpr( c == category::int8x8   ) return vorr_s8  (a, b);
    else  if constexpr( c == category::uint64x1 ) return vorr_u64 (a, b);
    else  if constexpr( c == category::uint32x2 ) return vorr_u32 (a, b);
    else  if constexpr( c == category::uint16x4 ) return vorr_u16 (a, b);
    else  if constexpr( c == category::uint8x8  ) return vorr_u8  (a, b);
    else  if constexpr( c == category::int64x2  ) return vorrq_s64(a, b);
    else  if constexpr( c == category::int32x4  ) return vorrq_s32(a, b);
    else  if constexpr( c == category::int16x8  ) return vorrq_s16(a, b);
    else  if constexpr( c == category::int8x16  ) return vorrq_s8 (a, b);
    else  if constexpr( c == category::uint64x2 ) return vorrq_u64(a, b);
    else  if constexpr( c == category::uint32x4 ) return vorrq_u32(a, b);
    else  if constexpr( c == category::uint16x8 ) return vorrq_u16(a, b);
    else  if constexpr( c == category::uint8x16 ) return vorrq_u8 (a, b);
    else  if constexpr( match(c, category::float_) )
    {
      constexpr auto tgt = as<as_uinteger_t<wide<T, N>>>{};
      return bit_cast(bit_or.behavior(current_api, opts, bit_cast(a, tgt), bit_cast(b, tgt)), as<wide<T, N>>{});
    }
  }
}
