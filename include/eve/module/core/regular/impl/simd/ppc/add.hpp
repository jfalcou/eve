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
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE upgrade_t<wide<T, N>> add_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
    requires (ppc_abi<abi_t<T, N>> && O::contains(widen))
  {
    return add.behavior(as<upgrade_t<wide<T, N>>>{}, cpu_{}, opts, v, w);
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> a, wide<T, N> b)
    requires (ppc_abi<abi_t<T, N>> && !O::contains(widen))
  {
    if constexpr (O::contains_any(lower, upper))
    {
      return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
    else if constexpr (O::contains(saturated) && std::integral<T>)
    {
      return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    }
    else
    {
      return vec_add(a.storage(), b.storage());
    }
  }
}
