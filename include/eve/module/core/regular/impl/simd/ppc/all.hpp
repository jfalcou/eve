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
  EVE_FORCEINLINE bool all_(EVE_REQUIRES(vmx_), O const& otps, logical<wide<T, N>> const& v) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    auto iv = v.bits();

    if constexpr (N::value == 1)
    {
      return static_cast<bool>(iv.get(0));
    }
    else
    {
      auto mask = expand_mask(otps[condition_key], as<wide<T, expected_cardinal_t<T, ppc_>>>{}).bits();

      if constexpr (N::value != expected_cardinal_v<T, ppc_>)
      {
        const auto of_mask = apply<N::value>([](auto... I) { return type {(I < N::value)...}; });
        mask &= of_mask.bits();
      }

      return vec_all_eq((iv & mask).storage(), mask.storage());
    }
  }
}
