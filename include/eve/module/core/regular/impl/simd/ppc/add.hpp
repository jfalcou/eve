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

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE  auto add_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires (ppc_abi<abi_t<T, N>> && (O::contains(narrow) || O::contains(widen)))
  {
    return add.behavior(cpu_{}, opts, v, w);
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> add_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> a, wide<T, N> b)
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(O::contains_any(narrow, widen) ||
                 (O::contains_any(lower, upper)  && floating_value<T>) ||
                 (O::contains(saturated) && std::integral<T>))
      return add.behavior(cpu_{}, opts, a, b);
    else
      return vec_add(a.storage(), b.storage());
  }
}
