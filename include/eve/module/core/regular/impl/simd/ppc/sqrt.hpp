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
#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/rsqrt.hpp>

namespace eve::detail
{
  template<floating_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE wide<T, N> sqrt_(EVE_REQUIRES(vmx_),
                                   O          const&,
                                   wide<T, N> const& v0) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    if constexpr( current_api >= vsx )
      return vec_sqrt(v0.storage());
    else
    {
      auto that = if_else(is_nez(v0), v0 * rsqrt(v0), v0);
      if constexpr( platform::supports_invalids && !O::contains(raw2))
        return if_else(v0 == inf(eve::as(v0)), v0, that);
      else
        return that;
    }
  }
}
