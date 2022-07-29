//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/skeleton.hpp>

#include <concepts>

namespace eve::detail
{
//================================================================================================
// +=
//================================================================================================
template<scalar_value T, value U, typename N>
EVE_FORCEINLINE decltype(auto)
self_add(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && wasm_abi<abi_t<T, N>>
{
  using type = wide<T, N>;

  if constexpr( scalar_value<U> ) { return self_add(self, type {other}); }
  else if constexpr( std::same_as<type, U> )
  {
    constexpr auto c = categorize<type>();

    if constexpr( c == category::float64x2 ) self = wasm_f64x2_add(self, other);
    else if constexpr( c == category::float32x4 ) self = wasm_f32x4_add(self, other);
    else if constexpr( c == category::int64x2 ) self = wasm_i64x2_add(self, other);
    else if constexpr( c == category::int32x4 ) self = wasm_i32x4_add(self, other);
    else if constexpr( c == category::int16x8 ) self = wasm_i16x8_add(self, other);
    else if constexpr( c == category::int8x16 ) self = wasm_i8x16_add(self, other);
    else if constexpr( c == category::uint64x2 ) self = wasm_i64x2_add(self, other);
    else if constexpr( c == category::uint32x4 ) self = wasm_i32x4_add(self, other);
    else if constexpr( c == category::uint16x8 ) self = wasm_i16x8_add(self, other);
    else if constexpr( c == category::uint8x16 ) self = wasm_i8x16_add(self, other);

    return self;
  }
}

//================================================================================================
// -=
//================================================================================================
template<scalar_value T, value U, typename N>
EVE_FORCEINLINE decltype(auto)
self_sub(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && wasm_abi<abi_t<T, N>>
{
  using type = wide<T, N>;

  if constexpr( scalar_value<U> ) { return self_sub(self, type {other}); }
  else if constexpr( std::same_as<type, U> )
  {
    constexpr auto c = categorize<type>();

    if constexpr( c == category::float64x2 ) self = wasm_f64x2_sub(self, other);
    else if constexpr( c == category::float32x4 ) self = wasm_f32x4_sub(self, other);
    else if constexpr( c == category::int64x2 ) self = wasm_i64x2_sub(self, other);
    else if constexpr( c == category::int32x4 ) self = wasm_i32x4_sub(self, other);
    else if constexpr( c == category::int16x8 ) self = wasm_i16x8_sub(self, other);
    else if constexpr( c == category::int8x16 ) self = wasm_i8x16_sub(self, other);
    else if constexpr( c == category::uint64x2 ) self = wasm_i64x2_sub(self, other);
    else if constexpr( c == category::uint32x4 ) self = wasm_i32x4_sub(self, other);
    else if constexpr( c == category::uint16x8 ) self = wasm_i16x8_sub(self, other);
    else if constexpr( c == category::uint8x16 ) self = wasm_i8x16_sub(self, other);

    return self;
  }
}

//================================================================================================
// *=
//================================================================================================
template<scalar_value T, value U, typename N>
EVE_FORCEINLINE decltype(auto)
self_mul(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && wasm_abi<abi_t<T, N>>
{
  using type = wide<T, N>;

  if constexpr( scalar_value<U> ) { return self_mul(self, type {other}); }
  else if constexpr( std::same_as<type, U> )
  {
    constexpr auto c = categorize<type>();

    if constexpr( c == category::float64x2 ) self = wasm_f64x2_mul(self, other);
    else if constexpr( c == category::float32x4 ) self = wasm_f32x4_mul(self, other);
    else if constexpr( c == category::int64x2 ) self = wasm_i64x2_mul(self, other);
    else if constexpr( c == category::int32x4 ) self = wasm_i32x4_mul(self, other);
    else if constexpr( c == category::int16x8 ) self = wasm_i16x8_mul(self, other);
    else if constexpr( c == category::int8x16 ) self = wasm_i8x16_mul(self, other);
    else if constexpr( c == category::uint64x2 ) self = wasm_i64x2_mul(self, other);
    else if constexpr( c == category::uint32x4 ) self = wasm_i32x4_mul(self, other);
    else if constexpr( c == category::uint16x8 ) self = wasm_i16x8_mul(self, other);
    else if constexpr( c == category::uint8x16 ) self = wasm_i8x16_mul(self, other);

    return self;
  }
}

//================================================================================================
// /=
//================================================================================================
template<scalar_value T, value U, typename N>
EVE_FORCEINLINE decltype(auto)
self_div(wide<T, N>& self, U const& other) noexcept
requires(scalar_value<U> || std::same_as<wide<T, N>, U>) && wasm_abi<abi_t<T, N>>
{
  using type = wide<T, N>;

  if constexpr( scalar_value<U> ) { return self_div(self, type {other}); }
  else if constexpr( std::same_as<type, U> )
  {
    constexpr auto c = categorize<type>();

    if constexpr( c == category::float64x2 ) self = wasm_f64x2_div(self, other);
    else if constexpr( c == category::float32x4 ) self = wasm_f32x4_div(self, other);
    else
    {
      auto           s    = self;
      constexpr auto sdiv = [](auto a, auto b) { return a /= b; };
      self                = map(sdiv, s, other);
    }

    return self;
  }
}
}
