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

namespace eve::detail
{
  template<callable_options O, floating_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> div_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(saturated))
    {
      return div.behavior(cpu_{}, opts, a, b);
    }
    else if constexpr (O::contains(toward_zero) || O::contains(upward) || O::contains(downward) || O::contains(to_nearest))
    {
      return round[opts](div(a, b));
    }
    else
    {
      return a.storage() / b.storage();
    }
  }
}
