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
#include <eve/module/core/constant/true.hpp>
#include <eve/detail/remove_garbage.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE bool all_(EVE_REQUIRES(vmx_), O const& opts, logical<wide<T, N>> v) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    const auto m = v.bits();

    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      return vec_all_eq(remove_garbage(m).storage(), true_(as(m)).storage());
    }
    else
    {
      const auto mask = expand_mask_no_garbage(opts[condition_key], as(v)).bits();
      return vec_all_eq((m & mask).storage(), mask.storage());
    }
  }
}
