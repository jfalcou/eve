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

namespace eve::detail
{
  template<callable_options O, typename T, typename N, arithmetic_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> w, wide<S, N> s) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    return shl.behavior(current_api, opts, w, -s);
  }

  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> w, S s) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    return shl.behavior(current_api, opts, w, -s);
  }

  template<callable_options O, typename T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(neon128_), O const&, wide<T,N> w, index_t<S>) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if       constexpr( S == 0 )                  return w;
    else  if constexpr( c == category::int64x1  ) return vshr_n_s64 (w, S);
    else  if constexpr( c == category::int32x2  ) return vshr_n_s32 (w, S);
    else  if constexpr( c == category::int16x4  ) return vshr_n_s16 (w, S);
    else  if constexpr( c == category::int8x8   ) return vshr_n_s8  (w, S);
    else  if constexpr( c == category::uint64x1 ) return vshr_n_u64 (w, S);
    else  if constexpr( c == category::uint32x2 ) return vshr_n_u32 (w, S);
    else  if constexpr( c == category::uint16x4 ) return vshr_n_u16 (w, S);
    else  if constexpr( c == category::uint8x8  ) return vshr_n_u8  (w, S);
    else  if constexpr( c == category::int64x2  ) return vshrq_n_s64(w, S);
    else  if constexpr( c == category::int32x4  ) return vshrq_n_s32(w, S);
    else  if constexpr( c == category::int16x8  ) return vshrq_n_s16(w, S);
    else  if constexpr( c == category::int8x16  ) return vshrq_n_s8 (w, S);
    else  if constexpr( c == category::uint64x2 ) return vshrq_n_u64(w, S);
    else  if constexpr( c == category::uint32x4 ) return vshrq_n_u32(w, S);
    else  if constexpr( c == category::uint16x8 ) return vshrq_n_u16(w, S);
    else  if constexpr( c == category::uint8x16 ) return vshrq_n_u8 (w, S);
  }
}
