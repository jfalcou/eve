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
  EVE_FORCEINLINE wide<T, N> div_(EVE_REQUIRES(vsx_),
                                  O const&,
                                  wide<T, N> v0,
                                  wide<T, N> const& v1) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr(O::contains(toward_zero2) || O::contains(upward2) || O::contains(downward2) || O::contains(to_nearest2))
      return round[o](div(v0, v1));
    else
    {
      return v0 /= v1;
    }
  }
}
