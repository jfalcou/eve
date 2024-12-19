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

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T,N> bit_not_(EVE_REQUIRES(neon128_), O const&, wide<T,N> w) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    using i_t = wide<as_integer_t<T, unsigned>, N>;

          if constexpr(c == category::int64x1 ) return vreinterpret_s64_s8(vmvn_s8(vreinterpret_s8_s64(w)));
    else  if constexpr(c == category::uint64x1) return vreinterpret_u64_u8(vmvn_u8(vreinterpret_u8_u64(w)));
    else  if constexpr(c == category::int64x2 ) return vreinterpretq_s64_s8(vmvnq_s8(vreinterpretq_s8_s64(w)));
    else  if constexpr(c == category::uint64x2) return vreinterpretq_u64_u8(vmvnq_u8(vreinterpretq_u8_u64(w)));
    else  if constexpr(c == category::int32x2 ) return vmvn_s32(w);
    else  if constexpr(c == category::uint32x2) return vmvn_u32(w);
    else  if constexpr(c == category::int32x4 ) return vmvnq_s32(w);
    else  if constexpr(c == category::uint32x4) return vmvnq_u32(w);
    else  if constexpr(c == category::int16x4 ) return vmvn_s16(w);
    else  if constexpr(c == category::uint16x4) return vmvn_u16(w);
    else  if constexpr(c == category::int16x8 ) return vmvnq_s16(w);
    else  if constexpr(c == category::uint16x8) return vmvnq_u16(w);
    else  if constexpr(c == category::int8x8  ) return vmvn_s8(w);
    else  if constexpr(c == category::uint8x8 ) return vmvn_u8(w);
    else  if constexpr(c == category::int8x16 ) return vmvnq_s8(w);
    else  if constexpr(c == category::uint8x16) return vmvnq_u8(w);
    else                                        return bit_cast(~bit_cast(w,as<i_t>{}), as(w));
  }
}
