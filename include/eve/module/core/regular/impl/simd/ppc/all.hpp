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
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(vmx_), O const& opts, logical<wide<T, N>> const& v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr (N::value == 1)
  {
    const auto m = v0.bits();

    if constexpr (match_option<condition_key, O, ignore_none_>)
    {
      return static_cast<bool>(m.get(0));
    }
    else
    {
      const auto cm = expand_mask(opts[condition_key], as<wide<T, N>>{});
      return static_cast<bool>(v0.get(0)) || !static_cast<bool>(cm.get(0));
    }
  }
  else
  {
    const auto m = simd_cast(v0, as<logical<wide<T>>>{});
    auto mask = simd_cast(expand_mask(opts[condition_key], as<wide<T, N>>{}), as<logical<wide<T>>>{});

    if constexpr (N::value != expected_cardinal_v<T, ppc_>)
    {
      logical<wide<T>> mm = [](auto i, auto) { return i < N::value; };
      mask = mask && mm;
    }

    return vec_all_eq((m && mask).bits().storage(), mask.bits().storage());
  }
}
}
