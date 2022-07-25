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
#include <eve/detail/function/load.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/as_integer.hpp>

namespace eve::detail
{
//================================================================================================
// Enumerated make
//================================================================================================
template<real_scalar_value T, typename S, typename... Vs>
EVE_FORCEINLINE auto
make(eve::as<wide<T, S>> const&, Vs... vs) noexcept requires sve_abi<abi_t<T, S>>
{
  static_assert(sizeof...(Vs) == S::value, "[eve::make] - Invalid number of arguments");
  std::array on_stack {static_cast<T>(vs)...};
  return load(on_stack.data(), S {});
}

template<real_scalar_value T, typename S, typename... Vs>
EVE_FORCEINLINE auto
make(eve::as<logical<wide<T, S>>> const&, Vs... vs) noexcept requires sve_abi<abi_t<T, S>>
{
  static_assert(sizeof...(Vs) == S::value, "[eve::make] - Invalid number of arguments");

  typename logical<wide<T, S>>::storage_type that {};
  [&]<std::size_t... N>(auto& v, std::index_sequence<N...>) { ((v |= vs ? (1ULL << N) : 0), ...); }
  (that.value, std::make_index_sequence<sizeof...(vs)> {});

  return that;
}

//================================================================================================
// splat make
//================================================================================================

template<real_scalar_value T, typename S, typename V>
EVE_FORCEINLINE auto
make(eve::as<logical<wide<T, S>>> const&, V v) noexcept requires sve_abi<abi_t<T, S>>
{
  using uint_t = make_integer_t<S::value / 8, unsigned>;
  typename logical<wide<T, S>>::storage_type that {};
  return static_cast<typename logical<wide<T, S>>::storage_type>(v ? (uint_t)-1 : (uint_t)0);
}

template<real_scalar_value T, typename S, typename V>
EVE_FORCEINLINE auto
make(eve::as<wide<T, S>> const&, V v_raw) noexcept requires sve_abi<abi_t<T, S>>
{
  T v = static_cast<T>(v_raw);

  if constexpr( wide<T, S>::size() == eve::expected_cardinal_v<T> )
  {
    if constexpr( std::same_as<T, double> ) return svdup_f64(v);
    else if constexpr( std::same_as<T, float> ) return svdup_f32(v);
    else if constexpr( std::same_as<T, std::int64_t> ) return svdup_s64(v);
    else if constexpr( std::same_as<T, std::uint64_t> ) return svdup_u64(v);
    else if constexpr( std::same_as<T, std::int32_t> ) return svdup_s32(v);
    else if constexpr( std::same_as<T, std::uint32_t> ) return svdup_u32(v);
    else if constexpr( std::same_as<T, std::int16_t> ) return svdup_s16(v);
    else if constexpr( std::same_as<T, std::uint16_t> ) return svdup_u16(v);
    else if constexpr( std::same_as<T, std::int8_t> ) return svdup_s8(v);
    else if constexpr( std::same_as<T, std::uint8_t> ) return svdup_u8(v);
  }
  else
  {
    // zero out top.
    auto m = make(as<logical<wide<T, S>>> {}, true);
    if constexpr( std::same_as<T, double> ) svdup_n_f64_m(0.0, m, v);
    else if constexpr( std::same_as<T, float> ) svdup_n_f32_m(0.0f, m, v);
    else if constexpr( std::same_as<T, std::int64_t> ) svdup_n_s64_m(0, m, v);
    else if constexpr( std::same_as<T, std::uint64_t> ) svdup_n_u64_m(0, m, v);
    else if constexpr( std::same_as<T, std::int32_t> ) svdup_n_s32_m(0, m, v);
    else if constexpr( std::same_as<T, std::uint32_t> ) svdup_n_u32_m(0, m, v);
    else if constexpr( std::same_as<T, std::int16_t> ) svdup_n_s16_m(0, m, v);
    else if constexpr( std::same_as<T, std::uint16_t> ) svdup_n_u16_m(0, m, v);
    else if constexpr( std::same_as<T, std::int8_t> ) svdup_n_s8_m(0, m, v);
    else if constexpr( std::same_as<T, std::uint8_t> ) svdup_n_u8_m(0, m, v);
  }
}

}
