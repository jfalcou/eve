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

namespace eve::detail
{
template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
trunc_(EVE_SUPPORTS(vmx_), wide<T, N> const& v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr( integral_value<T> ) return v0;
  else if constexpr( floating_value<T> ) return vec_trunc(v0.storage());
}

template<real_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
trunc_(EVE_SUPPORTS(vmx_), raw_type, wide<T, N> const& v0) noexcept requires ppc_abi<abi_t<T, N>>
{
  return trunc(v0);
}
}
