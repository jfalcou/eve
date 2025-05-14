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
template<scalar_value T, typename N, callable_options O>
EVE_FORCEINLINE bool
any_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T,N>> v) noexcept
requires sve_abi<abi_t<T, N>>
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cond = opts[condition_key];
  if constexpr(C::is_complete && ! C::is_inverted)  return false;
  else if constexpr (!relative_conditional_expr<C>) return svptest_any(remove_garbage(expand_mask(cond, as(v))), v);
  else                                              return svptest_any(sve_true(cond, as(v)) , v);
}
}
