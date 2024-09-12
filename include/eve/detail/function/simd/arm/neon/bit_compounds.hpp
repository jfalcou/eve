//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/function/bit_cast.hpp>

#include <concepts>
#include <cstddef>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, wide<U,N> s) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, signed>,N>;
    auto const si   = bit_cast(s,as<i_t>()).storage();

    constexpr auto c = categorize<wide<T, N>>();

          if constexpr( c == category::int64x1  ) v = vshl_s64(v, si);
    else  if constexpr( c == category::int32x2  ) v = vshl_s32(v, si);
    else  if constexpr( c == category::int16x4  ) v = vshl_s16(v, si);
    else  if constexpr( c == category::int8x8   ) v = vshl_s8 (v, si);
    else  if constexpr( c == category::uint64x1 ) v = vshl_u64(v, si);
    else  if constexpr( c == category::uint32x2 ) v = vshl_u32(v, si);
    else  if constexpr( c == category::uint16x4 ) v = vshl_u16(v, si);
    else  if constexpr( c == category::uint8x8  ) v = vshl_u8 (v, si);
    else  if constexpr( c == category::int64x2  ) v = vshlq_s64(v, si);
    else  if constexpr( c == category::int32x4  ) v = vshlq_s32(v, si);
    else  if constexpr( c == category::int16x8  ) v = vshlq_s16(v, si);
    else  if constexpr( c == category::int8x16  ) v = vshlq_s8 (v, si);
    else  if constexpr( c == category::uint64x2 ) v = vshlq_u64(v, si);
    else  if constexpr( c == category::uint32x4 ) v = vshlq_u32(v, si);
    else  if constexpr( c == category::uint16x8 ) v = vshlq_u16(v, si);
    else  if constexpr( c == category::uint8x16 ) v = vshlq_u8 (v, si);

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, U s) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, signed>,N>;
    v <<= i_t(s);
    return v;
  }

  template<integral_scalar_value T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, index_t<S> const&) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr(S != 0)
    {
            if constexpr( c == category::int64x1  ) v = vshl_n_s64 (v, S);
      else  if constexpr( c == category::int32x2  ) v = vshl_n_s32 (v, S);
      else  if constexpr( c == category::int16x4  ) v = vshl_n_s16 (v, S);
      else  if constexpr( c == category::int8x8   ) v = vshl_n_s8  (v, S);
      else  if constexpr( c == category::uint64x1 ) v = vshl_n_u64 (v, S);
      else  if constexpr( c == category::uint32x2 ) v = vshl_n_u32 (v, S);
      else  if constexpr( c == category::uint16x4 ) v = vshl_n_u16 (v, S);
      else  if constexpr( c == category::uint8x8  ) v = vshl_n_u8  (v, S);
      else  if constexpr( c == category::int64x2  ) v = vshlq_n_s64(v, S);
      else  if constexpr( c == category::int32x4  ) v = vshlq_n_s32(v, S);
      else  if constexpr( c == category::int16x8  ) v = vshlq_n_s16(v, S);
      else  if constexpr( c == category::int8x16  ) v = vshlq_n_s8 (v, S);
      else  if constexpr( c == category::uint64x2 ) v = vshlq_n_u64(v, S);
      else  if constexpr( c == category::uint32x4 ) v = vshlq_n_u32(v, S);
      else  if constexpr( c == category::uint16x8 ) v = vshlq_n_u16(v, S);
      else  if constexpr( c == category::uint8x16 ) v = vshlq_n_u8 (v, S);
    }

    return v;
  }

  //================================================================================================
  // >>=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, wide<U,N> s) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return self_shl(v, -s);
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, U s) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    return self_shl(v, -s);
  }

  template<integral_scalar_value T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, index_t<S> const&) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr(S != 0)
    {
      if       constexpr( c == category::int64x1  ) v = vshr_n_s64 (v, S);
      else  if constexpr( c == category::int32x2  ) v = vshr_n_s32 (v, S);
      else  if constexpr( c == category::int16x4  ) v = vshr_n_s16 (v, S);
      else  if constexpr( c == category::int8x8   ) v = vshr_n_s8  (v, S);
      else  if constexpr( c == category::uint64x1 ) v = vshr_n_u64 (v, S);
      else  if constexpr( c == category::uint32x2 ) v = vshr_n_u32 (v, S);
      else  if constexpr( c == category::uint16x4 ) v = vshr_n_u16 (v, S);
      else  if constexpr( c == category::uint8x8  ) v = vshr_n_u8  (v, S);
      else  if constexpr( c == category::int64x2  ) v = vshrq_n_s64(v, S);
      else  if constexpr( c == category::int32x4  ) v = vshrq_n_s32(v, S);
      else  if constexpr( c == category::int16x8  ) v = vshrq_n_s16(v, S);
      else  if constexpr( c == category::int8x16  ) v = vshrq_n_s8 (v, S);
      else  if constexpr( c == category::uint64x2 ) v = vshrq_n_u64(v, S);
      else  if constexpr( c == category::uint32x4 ) v = vshrq_n_u32(v, S);
      else  if constexpr( c == category::uint16x8 ) v = vshrq_n_u16(v, S);
      else  if constexpr( c == category::uint8x16 ) v = vshrq_n_u8 (v, S);
    }

    return v;
  }
}
