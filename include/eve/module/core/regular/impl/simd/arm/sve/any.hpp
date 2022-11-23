//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(sve_), C const& cond, logical<wide<T,N>> const& v) noexcept
requires sve_abi<abi_t<T, N>>
{
  if constexpr( C::is_complete && !C::is_inverted ) return false;
  else return svptest_any(cond.mask(as<wide<T,N>>{}),v);
}

template<scalar_value T, typename N>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(sve_), logical<wide<T,N>> v) noexcept
requires sve_abi<abi_t<T, N>>
{
  return svptest_any(detail::sve_true<T>(),v);
}
}
