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
  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(vmx_), O const&, wide<T, N> v, wide<S, N> s) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return vec_sl(v.storage(), convert(s, as<as_integer_t<T, unsigned>>{}).storage());
  }

  template<callable_options O, typename T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> shl_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> v, S s) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    return shl.behavior(current_api, opts, v, wide<as_integer_t<T, unsigned>, N>{s});
  }
}
