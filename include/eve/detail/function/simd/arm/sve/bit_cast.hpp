//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/simd.hpp>
#include <eve/detail/category.hpp>

namespace eve::detail
{
template<scalar_value T, typename N, scalar_value U, typename M>
EVE_FORCEINLINE wide<U, M>
bit_cast_(EVE_SUPPORTS(sve_), wide<T, N> const& x, as<wide<U, M>> const&) noexcept
requires(sizeof(wide<T, N>) == sizeof(wide<U, M>) && (sve_abi<abi_t<T, N>>))
{
  if constexpr( std::is_same_v<wide<T, N>, wide<U, M>> ) { return x; }
  else
  {
    auto as_byte = [](auto v)
    {
      constexpr auto c = categorize<eve::wide<T,N>>();
            if constexpr(match(c, category::float64)) return svreinterpret_u8_f64(v);
      else  if constexpr(match(c, category::float32)) return svreinterpret_u8_f32(v);
      else  if constexpr(match(c, category::int64)  ) return svreinterpret_u8_s64(v);
      else  if constexpr(match(c, category::uint64) ) return svreinterpret_u8_u64(v);
      else  if constexpr(match(c, category::int32)  ) return svreinterpret_u8_s32(v);
      else  if constexpr(match(c, category::uint32) ) return svreinterpret_u8_u32(v);
      else  if constexpr(match(c, category::int16)  ) return svreinterpret_u8_s16(v);
      else  if constexpr(match(c, category::uint16) ) return svreinterpret_u8_u16(v);
      else  if constexpr(match(c, category::int8)   ) return svreinterpret_u8_s8 (v);
      else  if constexpr(match(c, category::uint8)  ) return v.storage();
    }(x);

    constexpr auto d = categorize<wide<U, M>>();

            if constexpr(match(d, category::float64)) return svreinterpret_f64_u8(as_byte);
      else  if constexpr(match(d, category::float32)) return svreinterpret_f32_u8(as_byte);
      else  if constexpr(match(d, category::int64)  ) return svreinterpret_s64_u8(as_byte);
      else  if constexpr(match(d, category::uint64) ) return svreinterpret_u64_u8(as_byte);
      else  if constexpr(match(d, category::int32)  ) return svreinterpret_s32_u8(as_byte);
      else  if constexpr(match(d, category::uint32) ) return svreinterpret_u32_u8(as_byte);
      else  if constexpr(match(d, category::int16)  ) return svreinterpret_s16_u8(as_byte);
      else  if constexpr(match(d, category::uint16) ) return svreinterpret_u16_u8(as_byte);
      else  if constexpr(match(d, category::int8)   ) return svreinterpret_s8_u8 (as_byte);
      else  if constexpr(match(d, category::uint8)  ) return as_byte;
  }
}
}
