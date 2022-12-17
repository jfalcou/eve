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
template<signed_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>
minus_(EVE_SUPPORTS(sve_), wide<T, N> const& v) noexcept requires sve_abi<abi_t<T, N>>
{
  return -v;
}

template<conditional_expr C, signed_scalar_value T, typename N>
EVE_FORCEINLINE auto
minus_(EVE_SUPPORTS(sve_), C const& cond, wide<T, N> v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete && C::is_inverted ) return -v;
  else  return svneg_m(alternative(cond, v, as(v)), expand_mask(cond, as(v)), v);
}
}
