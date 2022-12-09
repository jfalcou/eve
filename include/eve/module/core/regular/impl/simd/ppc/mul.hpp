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
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
mul_(EVE_SUPPORTS(vmx_), wide<T, N> v0, wide<T, N> const& v1) noexcept requires ppc_abi<abi_t<T, N>>
{
  return v0 *= v1;
}
}
