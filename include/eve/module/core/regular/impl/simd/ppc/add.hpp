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
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE auto add_(EVE_REQUIRES(vmx_), O const& opts,
                            wide<T, N> a, wide<T, N> b)
    requires (ppc_abi<abi_t<T, N>>)
  {
    if constexpr (O::contains(widen))
      return add.behavior(as<upgrade_t<wide<T, N>>>{}, cpu_{}, opts, a, b);
    if constexpr (O::contains_any(lower, upper, widen) || (O::contains(saturated) && std::integral<T>))
      return add.behavior(as<wide<T, N>>{}, cpu_{}, opts, a, b);
    else
      return wide<T, N>(vec_add(a.storage(), b.storage()));
  }
}
