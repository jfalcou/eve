
//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
namespace eve::detail
{
template<scalar_value T, typename N>
EVE_FORCEINLINE auto
bit_notand_(EVE_SUPPORTS(rvv_), wide<T, N> const& v0, wide<T, N> const& v1) noexcept -> wide<T, N>
requires rvv_abi<abi_t<T, N>>
{
  auto v0_copy    = v0;
  auto bitnot_res = self_bitnot(v0_copy);
  return self_bitand(bitnot_res, v1);
}
}
