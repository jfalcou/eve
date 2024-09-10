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
    return shl.behavior(current_api, opts, v, -s);
  }

  template<callable_options O, integral_scalar_value T, typename N, integral_scalar_value I>
  EVE_FORCEINLINE wide<T, N> rshr_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, I s) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    return shl.behavior(current_api, opts, v, -s);
  }

  template<callable_options O, integral_scalar_value T, typename N, std::ptrdiff_t S>
  EVE_FORCEINLINE wide<T, N> rshr_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> v, index_t<S>) noexcept
    requires arm_abi<abi_t<T, N>>
  {
    return shl.behavior(current_api, opts, v, index<-S>);
  }
}
