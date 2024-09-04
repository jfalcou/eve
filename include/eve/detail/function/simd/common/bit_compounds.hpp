//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // >>=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE bit_value_t<wide<T, N>, U>& self_shr(wide<T,N>& v, wide<U,N> s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a >> b); };

    if constexpr(   is_aggregated_v<abi_t<T, N>>
                &&  is_aggregated_v<abi_t<U, N>>
                )                                     v = aggregate(ss, v, s);
    else                                              v = map(ss, v, s);

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, U s) noexcept
  {
    auto ss = []<typename V>(V a, auto b) { return static_cast<V>(a >> b); };

    if constexpr(is_aggregated_v<abi_t<T, N>>) v = aggregate(ss, v, s);
    else                                          v = map(ss, v, s);

    return v;
  }

  template<integral_scalar_value T, typename N, std::ptrdiff_t V>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, index_t<V> const&) noexcept
  {
    return self_shr(v,V);
  }
}
