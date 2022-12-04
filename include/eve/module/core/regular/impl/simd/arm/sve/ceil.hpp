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
  if constexpr( C::is_complete )
  {
    if constexpr( C::is_inverted )  return svrintp_x(sve_true<T>(), v);
    else                            return alternative(cond, v,as(v));
  }
  else
  {
    auto src = alternative(cond, v, as(v));
    auto m   = expand_mask(cond, as(v));
    return svrintp_m(src, m, v);
  }
}
}
