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
  EVE_FORCEINLINE auto mul_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires (ppc_abi<abi_t<T, N>> && !O::contains(mod))
  {
    if constexpr( O::contains_any(lower, upper, widen) || (O::contains(saturated) && std::integral<T>))
      return mul.behavior(cpu_{}, opts, a, b);
    else
      return wide<T, N>(vec_mul(a.storage(), b.storage()));
  }
}
