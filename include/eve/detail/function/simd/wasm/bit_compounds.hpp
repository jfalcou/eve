//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>

#include <concepts>

namespace eve::detail
{
//================================================================================================
// <<=
//================================================================================================
template<integral_real_scalar_value T, typename N, integral_real_scalar_value U>
EVE_FORCEINLINE decltype(auto)
self_shr(wide<T, N>& v, U s) noexcept requires wasm_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == int64x2 ) v = wasm_i64x2_shr(v, s);
  if constexpr( c == int32x4 ) v = wasm_i32x4_shr(v, s);
  if constexpr( c == int16x8 ) v = wasm_u16x8_shr(v, s);
  if constexpr( c == int8x16 ) v = wasm_i8x16_shr(v, s);
  if constexpr( c == uint64x2 ) v = wasm_u64x2_shr(v, s);
  if constexpr( c == uint32x4 ) v = wasm_u32x4_shr(v, s);
  if constexpr( c == uint16x8 ) v = wasm_u16x8_shr(v, s);
  if constexpr( c == uint8x16 ) v = wasm_u8x16_shr(v, s);
  return v;
}

//================================================================================================
// <<=
//================================================================================================
template<integral_real_scalar_value T, typename N, integral_real_scalar_value U>
EVE_FORCEINLINE decltype(auto)
self_shl(wide<T, N>& v, U s) noexcept requires wasm_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == int64x2 ) v = wasm_i64x2_shr(v, s);
  if constexpr( c == int32x4 ) v = wasm_i32x4_shr(v, s);
  if constexpr( c == int16x8 ) v = wasm_u16x8_shr(v, s);
  if constexpr( c == int8x16 ) v = wasm_i8x16_shr(v, s);
  if constexpr( c == uint64x2 ) v = wasm_i64x2_shr(v, s);
  if constexpr( c == uint32x4 ) v = wasm_i32x4_shr(v, s);
  if constexpr( c == uint16x8 ) v = wasm_i16x8_shr(v, s);
  if constexpr( c == uint8x16 ) v = wasm_i8x16_shr(v, s);
  return v;
}

//================================================================================================
// &=
//================================================================================================
template<scalar_value T, value U, typename N>
    EVE_FORCEINLINE decltype(auto)
    self_bitand(wide<T, N>& self, U const& other) noexcept
    requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
    && wasm_abi<abi_t<T, N>>
{
  if constexpr( scalar_value<U> )
  {
    using type = wide<T, N>;
    return self &= type {bit_cast(other, as<T> {})};
  }
  else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
  {
    self = wasm_v128_and(self, other);
    return self;
  }
}

//================================================================================================
// |=
//================================================================================================
template<scalar_value T, value U, typename N>
    EVE_FORCEINLINE decltype(auto)
    self_bitor(wide<T, N>& self, U const& other) noexcept
    requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
    && wasm_abi<abi_t<T, N>>
{
  if constexpr( scalar_value<U> )
  {
    using type = wide<T, N>;
    return self |= type {bit_cast(other, as<T> {})};
  }
  else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
  {
    self = wasm_v128_or(self, other);
    return self;
  }
}

//================================================================================================
// ^=
//================================================================================================
template<scalar_value T, value U, typename N>
    EVE_FORCEINLINE decltype(auto)
    self_bitxor(wide<T, N>& self, U const& other) noexcept
    requires((sizeof(wide<T, N>) == sizeof(U)) || (sizeof(T) == sizeof(U)))
    && wasm_abi<abi_t<T, N>>
{
  if constexpr( scalar_value<U> )
  {
    using type = wide<T, N>;
    return self ^= type {bit_cast(other, as<T> {})};
  }
  else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
  {
    self = wasm_v128_xor(self, other);
    return self;
  }
}
}
