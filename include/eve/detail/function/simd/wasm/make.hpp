//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/spy.hpp>

namespace eve::detail
{
//================================================================================================
// enumerated make - 128bits
//================================================================================================
template<real_scalar_value T, typename S, typename... Vs>
EVE_FORCEINLINE auto
make(eve::as<wide<T, S>>, Vs... vs) noexcept requires std::same_as<abi_t<T, S>, wasm_128_>
{
  static_assert(sizeof...(Vs) <= S::value, "[eve::make] - Invalid number of arguments");

  constexpr auto c = categorize<wide<T, S>>();
  using enum category;

  if constexpr( S::value == 2 )
  {
    if constexpr( c == float64x2 ) return wasm_f64x2_make(vs...);
    if constexpr( c == int64x2 ) return wasm_i64x2_make(vs...);
    if constexpr( c == uint64x2 ) return wasm_u64x2_make(vs...);
    if constexpr( c == float32x4 ) return wasm_f32x4_make(vs..., 0.f, 0.f);
    if constexpr( c == int32x4 ) return wasm_i32x4_make(vs..., 0, 0);
    if constexpr( c == uint32x4 ) return wasm_u32x4_make(vs..., 0, 0);
    if constexpr( c == int16x8 ) return wasm_i16x8_make(vs..., 0, 0, 0, 0, 0, 0);
    if constexpr( c == uint16x8 ) return wasm_u16x8_make(vs..., 0, 0, 0, 0, 0, 0);
    if constexpr( c == int8x16 )
      return wasm_i8x16_make(vs..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if constexpr( c == uint8x16 )
      return wasm_u8x16_make(vs..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  if constexpr( S::value == 4 )
  {
    if constexpr( c == float32x4 ) return wasm_f32x4_make(vs...);
    if constexpr( c == int32x4 ) return wasm_i32x4_make(vs...);
    if constexpr( c == uint32x4 ) return wasm_u32x4_make(vs...);
    if constexpr( c == int16x8 ) return wasm_i16x8_make(vs..., 0, 0, 0, 0);
    if constexpr( c == uint16x8 ) return wasm_u16x8_make(vs..., 0, 0, 0, 0);
    if constexpr( c == int8x16 ) return wasm_i8x16_make(vs..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    if constexpr( c == uint8x16 ) return wasm_u8x16_make(vs..., 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
  }

  if constexpr( S::value == 8 )
  {
    if constexpr( c == int16x8 ) return wasm_i16x8_make(vs...);
    if constexpr( c == uint16x8 ) return wasm_u16x8_make(vs...);
    if constexpr( c == int8x16 ) return wasm_i8x16_make(vs..., 0, 0, 0, 0, 0, 0, 0, 0);
    if constexpr( c == uint8x16 ) return wasm_u8x16_make(vs..., 0, 0, 0, 0, 0, 0, 0, 0);
  }

  if constexpr( S::value == 16 )
  {
    if constexpr( c == int8x16 ) return wasm_i8x16_make(vs...);
    if constexpr( c == uint8x16 ) return wasm_u8x16_make(vs...);
  }
}

//================================================================================================
// splat make
//================================================================================================
template<real_scalar_value T, typename S, typename V>
EVE_FORCEINLINE auto
make(eve::as<wide<T, S>> const&, V v) noexcept requires wasm_abi<abi_t<T, S>>
{
  if constexpr( wide<T, S>::size() < eve::fundamental_cardinal_v<T> )
  {
    return [&]<std::size_t... N>(std::index_sequence<N...> const&)
    {
      return make(as<wide<T, fundamental_cardinal_t<T>>> {}, (N < S::value ? v : 0)...);
    }
    (std::make_index_sequence<fundamental_cardinal_v<T>>());
  }
  else
  {
    constexpr auto c = categorize<wide<T, S>>();
    if constexpr( c == category::float64x2 ) return wasm_f64x2_splat(v);
    else if constexpr( c == category::float32x4 ) return wasm_f32x4_splat(v);
    else if constexpr( c == category::int8x16 ) return wasm_i8x16_splat(v);
    else if constexpr( c == category::int16x8 ) return wasm_i16x8_splat(v);
    else if constexpr( c == category::int32x4 ) return wasm_i32x4_splat(v);
    else if constexpr( c == category::int64x2 ) return wasm_i64x2_splat(v);
    else if constexpr( c == category::uint8x16 ) return wasm_u8x16_splat(v);
    else if constexpr( c == category::uint16x8 ) return wasm_u16x8_splat(v);
    else if constexpr( c == category::uint32x4 ) return wasm_u32x4_splat(v);
    else if constexpr( c == category::uint64x2 ) return wasm_u64x2_splat(v);
  }
}

//================================================================================================
// logical cases
//================================================================================================
template<real_scalar_value T, typename S, typename... Vs>
EVE_FORCEINLINE auto
make(as<logical<wide<T, S>>> const&, Vs... vs) noexcept requires wasm_abi<abi_t<T, S>>
{
  return make(as<wide<T, S>> {}, logical<T>(vs).mask()...);
}

template<real_scalar_value T, typename S, typename V>
EVE_FORCEINLINE auto
make(as<logical<wide<T, S>>> const&, V v) noexcept requires wasm_abi<abi_t<T, S>>
{
  return make(as<wide<T, S>> {}, logical<T>(v).mask());
}
}
