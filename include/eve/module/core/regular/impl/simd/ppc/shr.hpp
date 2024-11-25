//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(vmx_), O const&, wide<T,N> v, wide<U,N> s) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    using i_t = wide<as_integer_t<T, unsigned>, N>;

    auto s_c = convert(s, as<as_integer_t<T, unsigned>>{});

    if constexpr(std::is_signed_v<T>) return vec_sra(v.storage(), s_c.storage());
    else                              return vec_sr (v.storage(), s_c.storage());
  }

  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE wide<T, N> shr_(EVE_REQUIRES(vmx_), O const& opts, wide<T,N> v, U s) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return shr.behavior(as<wide<T, N>>{}, current_api, opts, v, wide<as_integer_t<T, unsigned>, N>{s});
  }
}
