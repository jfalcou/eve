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
#include <eve/module/core/regular/count_true.hpp>

namespace eve::detail
{
template<callable_options O, scalar_value T, typename N>
EVE_FORCEINLINE bool
all_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> v) noexcept
requires sve_abi<abi_t<T, N>>
{
  using C = rbr::result::fetch_t<condition_key, O>;
  auto cx = opts[condition_key];

  if constexpr( C::is_complete )
  {
    if constexpr( C::is_inverted )  return count_true(v) == N::value;
    else                            return true;
  }
  else
  {
    const auto masked_count = count_true[cx](v);

    if constexpr (relative_conditional_expr<C>) return masked_count == cx.count(as(v));
    else                                        return masked_count == count_true(expand_mask(cx, as(v)));
  }
}
}
