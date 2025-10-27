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
  EVE_FORCEINLINE auto bit_xor_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  {
    constexpr auto c = categorize<wide<T, N>>();

          if constexpr( c == category::int64x1  ) return veor_s64 (a, b);
    else  if constexpr( c == category::int32x2  ) return veor_s32 (a, b);
    else  if constexpr( c == category::int16x4  ) return veor_s16 (a, b);
    else  if constexpr( c == category::int8x8   ) return veor_s8  (a, b);
    else  if constexpr( c == category::uint64x1 ) return veor_u64 (a, b);
    else  if constexpr( c == category::uint32x2 ) return veor_u32 (a, b);
    else  if constexpr( c == category::uint16x4 ) return veor_u16 (a, b);
    else  if constexpr( c == category::uint8x8  ) return veor_u8  (a, b);
    else  if constexpr( c == category::int64x2  ) return veorq_s64(a, b);
    else  if constexpr( c == category::int32x4  ) return veorq_s32(a, b);
    else  if constexpr( c == category::int16x8  ) return veorq_s16(a, b);
    else  if constexpr( c == category::int8x16  ) return veorq_s8 (a, b);
    else  if constexpr( c == category::uint64x2 ) return veorq_u64(a, b);
    else  if constexpr( c == category::uint32x4 ) return veorq_u32(a, b);
    else  if constexpr( c == category::uint16x8 ) return veorq_u16(a, b);
    else  if constexpr( c == category::uint8x16 ) return veorq_u8 (a, b);
    else  if constexpr( match(c, category::float_) )
    {
      constexpr auto tgt = as<as_uinteger_t<wide<T, N>>>{};
      return bit_cast(bit_xor.behavior(current_api, opts, bit_cast(a, tgt), bit_cast(b, tgt)), as<wide<T, N>>{});
    }
  }
}
