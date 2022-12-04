//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<floating_scalar_value T, typename N>
EVE_FORCEINLINE auto
ceil_(EVE_SUPPORTS(sve_), wide<T, N> const& v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return ceil[ignore_none](v);
}

template<conditional_expr C,floating_scalar_value T, typename N>
EVE_FORCEINLINE auto
ceil_(EVE_SUPPORTS(sve_), C const& cond, wide<T, N> const& v) noexcept -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete && !C::is_inverted)  return alternative(cond, v,as(v));
  else return svrintp_m(alternative(cond, v, as(v)), cond.mask(as(v)), v);
}
}
