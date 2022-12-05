//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
fam_(EVE_SUPPORTS(sve_), wide<T, N> v0, wide<T, N> v1, wide<T, N> v2) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return fam[ignore_none](v0, v1, v2);
}

template<conditional_expr C, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
fam_(EVE_SUPPORTS(sve_), C cond, wide<T, N> v0, wide<T, N> v1, wide<T, N> v2) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  auto const alt = alternative(cond, v0, as(v0));
  if constexpr( C::is_complete && !C::is_inverted ) return alt;
  return svmla_m(cond.mask(as(v0)), alt, v1, v2);
}
}
