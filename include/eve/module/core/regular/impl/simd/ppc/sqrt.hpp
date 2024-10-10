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
  EVE_FORCEINLINE wide<T, N> sqrt_(EVE_REQUIRES(vmx_), O const& opts, wide<T, N> w) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr (O::contains(lower) || O::contains(upper))
    {
      return sqrt.behavior(as<wide<T, N>>{}, cpu_{}, opts, w);
    }
    else if constexpr (current_api >= vsx)
    {
      return vec_sqrt(w.storage());
    }
    else
    {
      auto that = if_else(is_nez(w), w * rsqrt(w), w);
      
      if constexpr (platform::supports_invalids && !O::contains(raw))
        return if_else(w == inf(eve::as{w}), w, that);
      else
        return that;
    }
  }
}
