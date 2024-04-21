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
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> floor_(EVE_REQUIRES(vmx_),
                                    O const& o,
                                    wide<T, N> const& v0) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(!O::contains(almost))
    {
      if constexpr( floating_value<T> )
        return vec_floor(v0.storage());
      else
        return v0;
    }
    else
      return floor_(EVE_TARGETS(cpu_), o, v0);
  }
}
