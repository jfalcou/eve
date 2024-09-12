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
#include <eve/detail/function/bit_cast.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, wide<U,N> s) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
    v = vec_sl(v.storage(), bit_cast(s,as<i_t>()).storage());
    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  requires ppc_abi<abi_t<T, N>>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, U s) noexcept
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
    v <<= i_t(s);
    return v;
  }

  //================================================================================================
  // >>=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  requires ppc_abi<abi_t<T, N>>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, wide<U,N> s) noexcept
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;

    if constexpr(std::is_signed_v<T>) v = vec_sra(v.storage(), bit_cast(s,as<i_t>()).storage());
    else                              v = vec_sr (v.storage(), bit_cast(s,as<i_t>()).storage());

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  requires ppc_abi<abi_t<T, N>>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, U s) noexcept
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
    v >>= i_t(s);
    return v;
  }
}
