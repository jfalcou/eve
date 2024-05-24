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
template<unsigned_scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> popcount_(EVE_REQUIRES(sve_),
                                     O const&,
                                     wide<T, N> v) noexcept
requires sve_abi<abi_t<T, N>>
{
  return  svcnt_x(sve_true<T>(), v);
}

template<conditional_expr C, unsigned_scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE wide<T, N> popcount_(EVE_SUPPORTS(sve_),
                                     C const& cond,
                                     O const&,
                                     wide<T, N> v) noexcept
requires sve_abi<abi_t<T, N>>
{
  auto alt = alternative(cond, v, as(v));
  if constexpr( C::is_complete )
    return alt;
  else
    return svcnt_m(alt, expand_mask(cond, as(v)), v);
}
}
