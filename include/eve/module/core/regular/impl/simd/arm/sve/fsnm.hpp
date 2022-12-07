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
EVE_FORCEINLINE auto
fsnm_(EVE_SUPPORTS(sve_), wide<T, N> v0, wide<T, N> v1, wide<T, N> v2) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return -fam(v0, v1, v2);
}
}
