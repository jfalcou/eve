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
template<conditional_expr C, arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE wide<T,N>
mul_(EVE_SUPPORTS(sve_), C const& cx, wide<T, N> const& v, wide<T, N> const& w) noexcept
requires sve_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete ) { return mul_(EVE_RETARGET(cpu_), cx, v, w); }
  else
  {
    if constexpr( !C::has_alternative )
    {
      auto m   = expand_mask(cx, as<wide<T, N>> {});
      return svmul_m(m,v,w);
    }
    else  return mul_(EVE_RETARGET(cpu_), cx, v, w); }
}
}
