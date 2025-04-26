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

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE bool any_(EVE_REQUIRES(vmx_), O const& opts, logical<wide<T, N>> v) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr (N::value == 1)
    {
      auto m = v.bits();

      if constexpr (match_option<condition_key, O, ignore_none_>)
      {
        return static_cast<bool>(m.get(0));
      }
      else
      {
        const auto cm = expand_mask(opts[condition_key], as<wide<T, N>>{});
        return static_cast<bool>(m.get(0)) && static_cast<bool>(cm.get(0));
      }
    }
    else
    {
      auto m = simd_cast(v, as<logical<wide<T>>>{}).bits();

      if constexpr (N::value != expected_cardinal_v<T, ppc_>)
      {
        logical<wide<T>> mm = [](auto i, auto) { return i < N::value; };
        m &= mm.bits();
      }

      if constexpr (!match_option<condition_key, O, ignore_none_>)
      {
        const auto cm = simd_cast(expand_mask(opts[condition_key], as<wide<T, N>>{}), as<logical<wide<T>>>{});
        m &= cm.bits();
      }

      return vec_any_eq(m.storage(), true_(as<logical<wide<T>>>).storage());
    }
  }
}
