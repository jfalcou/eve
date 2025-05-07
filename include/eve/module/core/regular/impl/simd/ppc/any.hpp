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
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(vmx_), O const& opts, logical<wide<T, N>> const& v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr (!match_option<condition_key, O, ignore_none_>) return any.behavior(cpu_{}, opts, v0);
  auto m = v0.bits();

  if constexpr( N::value == 1 ) { return static_cast<bool>(m.get(0)); }
  else if constexpr( N::value == expected_cardinal_v<T, ppc_> )
  {
    return vec_any_eq(m.storage(), true_(eve::as(v0)).storage());
  }
  else
  {
    logical<wide<T>> mm = [](auto i, auto) { return i < N::value; };
    m &= bit_cast(mm, as<logical<wide<T, N>>>()).bits();

    return vec_any_eq(m.storage(), true_(eve::as(mm)).storage());
  }
}
}
