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
#include <eve/arch/arm/sve/sve_true.hpp>

namespace eve::detail
{
template<scalar_value T, typename N, relative_conditional_expr C>
EVE_FORCEINLINE bool
any_(EVE_SUPPORTS(sve_), C const& cond, logical<wide<T,N>> v) noexcept
requires sve_abi<abi_t<T, N>>
{
  if constexpr(C::is_complete && ! C::is_inverted)  return false;
  else                                              return svptest_any(sve_true(cond, as(v)) , v);
}
}
