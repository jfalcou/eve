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
  template<arithmetic_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> ceil_(EVE_SUPPORTS(vmx_),
                                   O const& o,
                                   wide<T, N> const& v0) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(!O::contains(almost2))
    {
      if constexpr( floating_value<T> )
        return vec_ceil(v0.storage());
      else return v0;
    }
    else
      return ceil_(EVE_TARGETS(cpu_), o, v0);
  }
}
