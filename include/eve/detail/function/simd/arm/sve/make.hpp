//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/arch/fundamental_cardinal.hpp>
#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/simd/arm/sve/iota.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/as_integer.hpp>

namespace eve::detail
{
//============================s====================================================================
// Enumerated make
//================================================================================================
template<arithmetic_scalar_value T, typename N, typename... Vs>
EVE_FORCEINLINE auto
make(eve::as<wide<T, N>>, Vs... vs) noexcept
requires sve_abi<abi_t<T, N>>
{
  static_assert(sizeof...(Vs) == N::value, "[eve::make] - Invalid number of arguments");

  if constexpr( wide<T, N>::size() < eve::fundamental_cardinal_v<T> )
  {
    return [&]<std::size_t... i>(std::index_sequence<i...>)
    {
      return make(as<wide<T, fundamental_cardinal_t<T>>> {}, vs..., ((void)i, 0)...);
    }
    (std::make_index_sequence<fundamental_cardinal_v<T> - N::value> {});
  }
  else
  {
    std::array on_stack {static_cast<T>(vs)...};
    return load(on_stack.data(), N {});
  }
}

//================================================================================================
// splat make
//================================================================================================
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
make(eve::as<wide<T, N>>, T x) noexcept
requires sve_abi<abi_t<T, N>> && (N::value > 1)
{
  // This may be suboptimal, we a one instruction iota on sve
  if constexpr( N::value < eve::fundamental_cardinal_v<T> )
  {
    // Use svdup then mask using optimized iota comparison
    return wide<T>{x} & (linear_ramp(as<wide<as_integer_t<T>>>{}) < N::value).mask();
  }
  else
  {
    constexpr auto c = categorize<wide<T, N>>();

    if constexpr( match(c, category::int8) ) return svdup_s8(x);
    else if constexpr( match(c, category::uint8) ) return svdup_u8(x);
    else if constexpr( match(c, category::int16) ) return svdup_s16(x);
    else if constexpr( match(c, category::uint16) ) return svdup_u16(x);
    else if constexpr( match(c, category::int32) ) return svdup_s32(x);
    else if constexpr( match(c, category::uint32) ) return svdup_u32(x);
    else if constexpr( match(c, category::int64) ) return svdup_s64(x);
    else if constexpr( match(c, category::uint64) ) return svdup_u64(x);
    else if constexpr( match(c, category::float32) ) return svdup_f32(x);
    else if constexpr( match(c, category::float64) ) return svdup_f64(x);
  }
}

//================================================================================================
// logical cases
//================================================================================================
template<arithmetic_scalar_value T, typename N, typename... Vs>
EVE_FORCEINLINE auto
make(as<logical<wide<T, N>>>, Vs... vs) noexcept
requires sve_abi<abi_t<T, N>>
{
  using bits_type = typename logical<wide<T, N>>::bits_type;
  using e_t       = element_type_t<bits_type>;

  auto bits = make(as<bits_type> {}, (vs ? (e_t)-1 : 0)...);
  return svcmpne(sve_true<T>(), bits, (e_t)0);
}

template<arithmetic_scalar_value T, typename N, typename V>
EVE_FORCEINLINE auto
make(eve::as<logical<wide<T, N>>>, V x) noexcept
requires sve_abi<abi_t<T, N>> && (N::value > 1)
{
  using f_t = fundamental_cardinal_t<T>;

  if constexpr( N::value < f_t::value )
  {
    // Use svdup then mask using optimized iota comparison
    return logical<wide<T>>{(bool)x} && (linear_ramp(as<wide<as_integer_t<T>>>{}) < N::value);
  }
  else
  {
    if constexpr( sizeof(T) == 1 ) return svdup_b8(x);
    else if constexpr( sizeof(T) == 2 ) return svdup_b16(x);
    else if constexpr( sizeof(T) == 4 ) return svdup_b32(x);
    else if constexpr( sizeof(T) == 8 ) return svdup_b64(x);
  }
}

}
