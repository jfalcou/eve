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
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(neon128_), O const&, wide<T, N> w, wide<S, N> s) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    auto const si = convert(s, as<as_integer_t<T, signed>>());

    constexpr auto c = categorize<wide<T, N>>();

         if constexpr( c == category::int64x1  ) return vshl_s64(w, si);
    else if constexpr( c == category::int32x2  ) return vshl_s32(w, si);
    else if constexpr( c == category::int16x4  ) return vshl_s16(w, si);
    else if constexpr( c == category::int8x8   ) return vshl_s8 (w, si);
    else if constexpr( c == category::uint64x1 ) return vshl_u64(w, si);
    else if constexpr( c == category::uint32x2 ) return vshl_u32(w, si);
    else if constexpr( c == category::uint16x4 ) return vshl_u16(w, si);
    else if constexpr( c == category::uint8x8  ) return vshl_u8 (w, si);
    else if constexpr( c == category::int64x2  ) return vshlq_s64(w, si);
    else if constexpr( c == category::int32x4  ) return vshlq_s32(w, si);
    else if constexpr( c == category::int16x8  ) return vshlq_s16(w, si);
    else if constexpr( c == category::int8x16  ) return vshlq_s8 (w, si);
    else if constexpr( c == category::uint64x2 ) return vshlq_u64(w, si);
    else if constexpr( c == category::uint32x4 ) return vshlq_u32(w, si);
    else if constexpr( c == category::uint16x8 ) return vshlq_u16(w, si);
    else if constexpr( c == category::uint8x16 ) return vshlq_u8 (w, si);
  }

  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> w, S s) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    return shl.behavior(current_api, opts, w, wide<as_integer_t<T, signed>, N>{s});
  }

  template<callable_options O, typename T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(neon128_), O const&, wide<T, N> w, index_t<S>) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr(S != 0)
    {
           if constexpr( c == category::int64x1  ) return vshl_n_s64 (w, S);
      else if constexpr( c == category::int32x2  ) return vshl_n_s32 (w, S);
      else if constexpr( c == category::int16x4  ) return vshl_n_s16 (w, S);
      else if constexpr( c == category::int8x8   ) return vshl_n_s8  (w, S);
      else if constexpr( c == category::uint64x1 ) return vshl_n_u64 (w, S);
      else if constexpr( c == category::uint32x2 ) return vshl_n_u32 (w, S);
      else if constexpr( c == category::uint16x4 ) return vshl_n_u16 (w, S);
      else if constexpr( c == category::uint8x8  ) return vshl_n_u8  (w, S);
      else if constexpr( c == category::int64x2  ) return vshlq_n_s64(w, S);
      else if constexpr( c == category::int32x4  ) return vshlq_n_s32(w, S);
      else if constexpr( c == category::int16x8  ) return vshlq_n_s16(w, S);
      else if constexpr( c == category::int8x16  ) return vshlq_n_s8 (w, S);
      else if constexpr( c == category::uint64x2 ) return vshlq_n_u64(w, S);
      else if constexpr( c == category::uint32x4 ) return vshlq_n_u32(w, S);
      else if constexpr( c == category::uint16x8 ) return vshlq_n_u16(w, S);
      else if constexpr( c == category::uint8x16 ) return vshlq_n_u8 (w, S);
    }
    else
    {
      return w;
    }
  }
}
