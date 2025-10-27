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
template<typename T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> bit_andnot_(EVE_REQUIRES(neon128_),
                                       O const          &opts,
                                       wide<T, N> const &v0,
                                       wide<T, N> const &v1) noexcept
requires arm_abi<abi_t<T, N>>
{
  constexpr auto cat = categorize<wide<T, N>>();

  if      constexpr( cat == category::int64x1 ) return vbic_s64(v0, v1);
  else if constexpr( cat == category::int32x2 ) return vbic_s32(v0, v1);
  else if constexpr( cat == category::int16x4 ) return vbic_s16(v0, v1);
  else if constexpr( cat == category::int8x8 ) return vbic_s8(v0, v1);
  else if constexpr( cat == category::uint64x1 ) return vbic_u64(v0, v1);
  else if constexpr( cat == category::uint32x2 ) return vbic_u32(v0, v1);
  else if constexpr( cat == category::uint16x4 ) return vbic_u16(v0, v1);
  else if constexpr( cat == category::uint8x8 ) return vbic_u8(v0, v1);
  else if constexpr( cat == category::int64x2 ) return vbicq_s64(v0, v1);
  else if constexpr( cat == category::int32x4 ) return vbicq_s32(v0, v1);
  else if constexpr( cat == category::int16x8 ) return vbicq_s16(v0, v1);
  else if constexpr( cat == category::int8x16 ) return vbicq_s8(v0, v1);
  else if constexpr( cat == category::uint64x2 ) return vbicq_u64(v0, v1);
  else if constexpr( cat == category::uint32x4 ) return vbicq_u32(v0, v1);
  else if constexpr( cat == category::uint16x8 ) return vbicq_u16(v0, v1);
  else if constexpr( cat == category::uint8x16 ) return vbicq_u8(v0, v1);
  else  if constexpr( match(cat, category::float_) )
  {
    constexpr auto tgt = as<as_uinteger_t<wide<T, N>>>{};
    return bit_cast(bit_andnot.behavior(current_api, opts, bit_cast(v0, tgt), bit_cast(v1, tgt)), as<wide<T, N>>{});
  }
}
}
