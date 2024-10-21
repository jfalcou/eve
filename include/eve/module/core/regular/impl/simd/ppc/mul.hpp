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
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE upgrade_t<wide<T, N>> mul_(EVE_REQUIRES(vmx_), O const& opts,
                                              wide<T, N> v, wide<T, N> w) noexcept
  requires (ppc_abi<abi_t<T, N>> && O::contains(widen))
  {
    return mul.behavior(cpu_{}, opts, v, w);
  }

  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_REQUIRES(vmx_), O const &opts,
                                  wide<T, N> a, wide<T, N> b) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(saturated) && integral_value<T>) return mul.behavior(cpu_{}, opts, a, b);
    else                                                        return a.storage() * b.storage();
  }
}
