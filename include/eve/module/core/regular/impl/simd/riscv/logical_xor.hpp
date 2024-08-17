//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
namespace eve::detail
{
template<arithmetic_scalar_value T, typename N, scalar_value U>
EVE_FORCEINLINE logical<wide<T, N>>
                logical_xor_(EVE_SUPPORTS(rvv_),
                             logical<wide<T, N>> const                &a,
                             logical<wide<U, N>> const                &b) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return a != bit_cast(b, as<logical<wide<T, N>>> {});
}
}
