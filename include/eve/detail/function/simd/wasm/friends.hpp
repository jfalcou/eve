//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
//==================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_lognot(logical<wide<T, N>> v) noexcept requires wasm_abi<abi_t<T, N>>
{
  return bit_cast(~v.bits(), as(v));
}

//==================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> v, wide<T, N> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  using type       = as_logical_t<wide<T, N>>;
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == float64x2 ) return type {wasm_f64x2_eq(v, w)};
  else if constexpr( c == float32x4 ) return type {wasm_f32x4_eq(v, w)};
  else if constexpr( c == int8x16 ) return type {wasm_i8x16_eq(v, w)};
  else if constexpr( c == int16x8 ) return type {wasm_i16x8_eq(v, w)};
  else if constexpr( c == int32x4 ) return type {wasm_i32x4_eq(v, w)};
  else if constexpr( c == int64x2 ) return type {wasm_i64x2_eq(v, w)};
  else if constexpr( c == uint8x16 ) return type {wasm_i8x16_eq(v, w)};
  else if constexpr( c == uint16x8 ) return type {wasm_i16x4_eq(v, w)};
  else if constexpr( c == uint32x4 ) return type {wasm_i32x4_eq(v, w)};
  else if constexpr( c == uint64x2 ) return type {wasm_i64x2_eq(v, w)};
}

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_eq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  return bit_cast(v.bits() == w.bits(), as(v));
}

//==================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> v, wide<T, N> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  using type       = as_logical_t<wide<T, N>>;
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == float64x2 ) return type {wasm_f64x2_ne(v, w)};
  else if constexpr( c == float32x4 ) return type {wasm_f32x4_ne(v, w)};
  else if constexpr( c == int8x16 ) return type {wasm_i8x16_ne(v, w)};
  else if constexpr( c == int16x8 ) return type {wasm_i16x8_ne(v, w)};
  else if constexpr( c == int32x4 ) return type {wasm_i32x4_ne(v, w)};
  else if constexpr( c == int64x2 ) return type {wasm_i64x2_ne(v, w)};
  else if constexpr( c == uint8x16 ) return type {wasm_i8x16_ne(v, w)};
  else if constexpr( c == uint16x8 ) return type {wasm_i16x4_ne(v, w)};
  else if constexpr( c == uint32x4 ) return type {wasm_i32x4_ne(v, w)};
  else if constexpr( c == uint64x2 ) return type {wasm_i64x2_ne(v, w)};
}

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_neq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  return bit_cast(v.bits() == w.bits(), as(v));
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_less(wide<T, N> v, wide<T, N> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  using type       = as_logical_t<wide<T, N>>;
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == float64x2 ) return type {wasm_f64x2_lt(v, w)};
  else if constexpr( c == float32x4 ) return type {wasm_f32x4_lt(v, w)};
  else if constexpr( c == int8x16 ) return type {wasm_i8x16_lt(v, w)};
  else if constexpr( c == int16x8 ) return type {wasm_i16x8_lt(v, w)};
  else if constexpr( c == int32x4 ) return type {wasm_i32x4_lt(v, w)};
  else if constexpr( c == int64x2 ) return type {wasm_i64x2_lt(v, w)};
  else if constexpr( c == uint8x16 ) return type {wasm_u8x16_lt(v, w)};
  else if constexpr( c == uint16x8 ) return type {wasm_u16x4_lt(v, w)};
  else if constexpr( c == uint32x4 ) return type {wasm_u32x4_lt(v, w)};
  else if constexpr( c == uint64x2 ) return type {wasm_u64x2_lt(v, w)};
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_greater(wide<T, N> v, wide<T, N> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  using type       = as_logical_t<wide<T, N>>;
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == float64x2 ) return type {wasm_f64x2_gt(v, w)};
  else if constexpr( c == float32x4 ) return type {wasm_f32x4_gt(v, w)};
  else if constexpr( c == int8x16 ) return type {wasm_i8x16_gt(v, w)};
  else if constexpr( c == int16x8 ) return type {wasm_i16x8_gt(v, w)};
  else if constexpr( c == int32x4 ) return type {wasm_i32x4_gt(v, w)};
  else if constexpr( c == int64x2 ) return type {wasm_i64x2_gt(v, w)};
  else if constexpr( c == uint8x16 ) return type {wasm_u8x16_gt(v, w)};
  else if constexpr( c == uint16x8 ) return type {wasm_u16x4_gt(v, w)};
  else if constexpr( c == uint32x4 ) return type {wasm_u32x4_gt(v, w)};
  else if constexpr( c == uint64x2 ) return type {wasm_u64x2_gt(v, w)};
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> v, wide<T, N> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  using type       = as_logical_t<wide<T, N>>;
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == float64x2 ) return type {wasm_f64x2_ge(v, w)};
  else if constexpr( c == float32x4 ) return type {wasm_f32x4_ge(v, w)};
  else if constexpr( c == int8x16 ) return type {wasm_i8x16_ge(v, w)};
  else if constexpr( c == int16x8 ) return type {wasm_i16x8_ge(v, w)};
  else if constexpr( c == int32x4 ) return type {wasm_i32x4_ge(v, w)};
  else if constexpr( c == int64x2 ) return type {wasm_i64x2_ge(v, w)};
  else if constexpr( c == uint8x16 ) return type {wasm_u8x16_ge(v, w)};
  else if constexpr( c == uint16x8 ) return type {wasm_u16x4_ge(v, w)};
  else if constexpr( c == uint32x4 ) return type {wasm_u32x4_ge(v, w)};
  else if constexpr( c == uint64x2 ) return type {wasm_u64x2_ge(v, w)};
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> v, wide<T, N> w) noexcept requires wasm_abi<abi_t<T, N>>
{
  using type       = as_logical_t<wide<T, N>>;
  constexpr auto c = categorize<wide<T, N>>();
  using enum category;

  if constexpr( c == float64x2 ) return type {wasm_f64x2_le(v, w)};
  else if constexpr( c == float32x4 ) return type {wasm_f32x4_le(v, w)};
  else if constexpr( c == int8x16 ) return type {wasm_i8x16_le(v, w)};
  else if constexpr( c == int16x8 ) return type {wasm_i16x8_le(v, w)};
  else if constexpr( c == int32x4 ) return type {wasm_i32x4_le(v, w)};
  else if constexpr( c == int64x2 ) return type {wasm_i64x2_le(v, w)};
  else if constexpr( c == uint8x16 ) return type {wasm_u8x16_le(v, w)};
  else if constexpr( c == uint16x8 ) return type {wasm_u16x4_le(v, w)};
  else if constexpr( c == uint32x4 ) return type {wasm_u32x4_le(v, w)};
  else if constexpr( c == uint64x2 ) return type {wasm_u64x2_le(v, w)};
}
}
