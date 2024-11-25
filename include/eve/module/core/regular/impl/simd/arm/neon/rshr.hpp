//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/shl.hpp>

namespace eve::detail
{
  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value S>
  EVE_FORCEINLINE wide<T, N> rshr_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, wide<S, N> s) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    return shl.behavior(as<wide<T, N>>{}, current_api, opts, v, -s);
  }

  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value I>
  EVE_FORCEINLINE wide<T, N> rshr_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, I s) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    return shl.behavior(as<wide<T, N>>{}, current_api, opts, v, -s);
  }

  template<callable_options O, integral_scalar_value T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE wide<T, N> rshr_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, index_t<S> s) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    if constexpr (S == 0)     return v;
    else if constexpr (S < 0) return shl.behavior(as<wide<T, N>>{}, current_api, opts, v, index<-S>);
    else                      return shr.behavior(as<wide<T, N>>{}, current_api, opts, v, s);
  }
}
