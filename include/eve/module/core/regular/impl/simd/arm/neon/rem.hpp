//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/skeleton_calls.hpp>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> rem_(EVE_REQUIRES(neon128_),
                                O const&,
                                wide<T, N>        v0,
                                wide<T, N> const &v1) noexcept requires arm_abi<abi_t<T, N>>

{
  if constexpr( current_api == neon ) return map(rem, v0, v1);
  else return rem.behavior(cpu_{}, v0, v1);
}
}
