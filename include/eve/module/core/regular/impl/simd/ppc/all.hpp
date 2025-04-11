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
  EVE_FORCEINLINE bool all_(EVE_REQUIRES(vmx_), O const& opts, logical<wide<T, N>> const& v) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr (N::value == 1)
    {
      const auto iv = v.bits();
      return static_cast<bool>(iv.get(0)) || !static_cast<bool>(expand_mask(opts[condition_key], as<wide<T, N>>{}).get(0));
    }
    else
    {
      using ec_t = expected_cardinal_t<T, ppc_>;
      using ew_t = logical<wide<T, ec_t>>;

      const auto vv  = simd_cast(v, as<ew_t>{});
      auto mask = simd_cast(expand_mask(opts[condition_key], as<wide<T, N>>{}), as<ew_t>{});

      // mask the inactive lanes
      if constexpr (N::value != expected_cardinal_v<T, ppc_>)
      {
        mask = mask && apply<ec_t::value>([](auto... I) { return ew_t {(I < N::value)...}; });
      }

      return vec_all_eq((vv && mask).bits().storage(), mask.bits().storage());
    }
  }
}
