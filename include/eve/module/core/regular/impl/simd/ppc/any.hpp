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
#include <eve/module/core/regular/simd_cast.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE bool any_(EVE_REQUIRES(vmx_), O const& opts, logical<wide<T, N>> v) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    auto m = v.bits();

    if constexpr (N::value == 1)
    {
      if constexpr (match_option<condition_key, O, ignore_none_>)
      {
        return static_cast<bool>(m.get(0));
      }
      else
      {
        const auto cm = expand_mask(opts[condition_key], as(v));
        return static_cast<bool>(m.get(0)) && static_cast<bool>(cm.get(0));
      }
    }
    else
    {
      if constexpr (match_option<condition_key, O, ignore_none_>)
      {
        m = remove_garbage(m);
      }
      else 
      {
        m &= expand_mask_remove_garbage(opts[condition_key], as(v)).bits();
      }

      return vec_any_eq(m.storage(), true_(as(m)).storage());
    }
  }
}
