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
bit_andnot_(EVE_SUPPORTS(rvv_), wide<T, N> const& v0, wide<T, N> const& v1) noexcept -> wide<T, N>
requires rvv_abi<abi_t<T, N>>
{
  auto v1_copy = v1;
  auto not_res = self_bitnot(v1_copy);
  auto v0_copy = v0;
  return self_bitand(v0_copy, not_res);
}
}
