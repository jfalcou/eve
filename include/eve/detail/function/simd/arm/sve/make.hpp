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
#include <eve/module/core/constant/iota.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/as_integer.hpp>

namespace eve::detail
{

template<callable_options O, arithmetic_scalar_value T, typename N, typename V0, typename... Vs>
requires sve_abi<abi_t<T, N>>
EVE_FORCEINLINE auto make_(EVE_REQUIRES(sve_), O const&, as<wide<T, N>>, V0 v, Vs... vs) noexcept
{
  if constexpr (sizeof...(Vs) == 0)
  {
    // This may be suboptimal, we a one instruction iota on sve
    if constexpr(N::value <  fundamental_cardinal_t<T>::value)
    {
      // Use svdup then mask using optimized iota comparison
      return wide<T>{v} & (iota(as<wide<as_integer_t<T>>>{}) < N::value).mask();
    }
    else
    {
      constexpr auto c = categorize<wide<T, N>>();

      if constexpr( match(c, category::int8) ) return svdup_s8(v);
      else if constexpr( match(c, category::uint8) ) return svdup_u8(v);
      else if constexpr( match(c, category::int16) ) return svdup_s16(v);
      else if constexpr( match(c, category::uint16) ) return svdup_u16(v);
      else if constexpr( match(c, category::int32) ) return svdup_s32(v);
      else if constexpr( match(c, category::uint32) ) return svdup_u32(v);
      else if constexpr( match(c, category::int64) ) return svdup_s64(v);
      else if constexpr( match(c, category::uint64) ) return svdup_u64(v);
      else if constexpr( match(c, category::float32) ) return svdup_f32(v);
      else if constexpr( match(c, category::float64) ) return svdup_f64(v);
    }
  }
  else
  {
    static_assert((sizeof...(Vs) + 1) == N::value, "[eve::make] - Invalid number of arguments");

    if constexpr( wide<T, N>::size() < eve::fundamental_cardinal_v<T> )
    {
      return [&]<std::size_t... i>(std::index_sequence<i...>)
      {
        return make(as<wide<T, fundamental_cardinal_t<T>>> {}, v, vs..., ((void)i, 0)...);
      }
      (std::make_index_sequence<fundamental_cardinal_v<T> - N::value> {});
    }
    else
    {
      std::array on_stack {v, static_cast<T>(vs)...};
      return load(on_stack.data(), N {});
    }
  }
}

template<callable_options O, arithmetic_scalar_value T, typename N, typename V0, typename... Vs>
requires sve_abi<abi_t<T, N>>
EVE_FORCEINLINE auto make_(EVE_REQUIRES(sve_), O const&, as<logical<wide<T, N>>>, V0 v, Vs... vs) noexcept
{
  if constexpr (sizeof...(Vs) == 0)
  {
    if constexpr(N::value < fundamental_cardinal_t<T>::value)
    {
      // Use svdup then mask using optimized iota comparison
      return logical<wide<T>>{(bool) v} && (iota(as<wide<as_integer_t<T>>>{}) < N::value);
    }
    else
    {
      if constexpr( sizeof(T) == 1 ) return svdup_b8(v);
      else if constexpr( sizeof(T) == 2 ) return svdup_b16(v);
      else if constexpr( sizeof(T) == 4 ) return svdup_b32(v);
      else if constexpr( sizeof(T) == 8 ) return svdup_b64(v);
    }
  }
  else
  {
    using bits_type = typename logical<wide<T, N>>::bits_type;
    using e_t       = element_type_t<bits_type>;

    auto bits = make(as<bits_type> {}, static_cast<e_t>(v ? -1 : 0), static_cast<e_t>(vs ? -1 : 0)...);
    return svcmpne(sve_true<T>(), bits, e_t{0});
  }
}

}
