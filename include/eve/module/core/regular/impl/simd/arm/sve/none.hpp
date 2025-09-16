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
#include <eve/module/core/regular/logical_ornot.hpp>
#include <eve/module/core/regular/any.hpp>

namespace eve::detail
{
  template<callable_options O, scalar_value T, typename N>
  EVE_FORCEINLINE auto none_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (O::contains(splat))
    {
      // two constructors to allow the compiler to understand that we want to splat but still communicate the "real"
      // size of the operands to eve::equal
      auto zero_splat = wide<T, N> { wide<T> { 0 } };

      if constexpr (C::is_complete)
      {
        if constexpr (C::is_inverted) return wide<T, N> { wide<T> { count_true(v) } } == zero_splat;
        else                          return logical<wide<T, N>> { true };
      }
      else if constexpr (relative_conditional_expr<C>)
      {
        return wide<T, N> { wide<T> { count_true[cx](v) } } == zero_splat;
      }
      else
      {
        return wide<T, N> { wide<T> { count_true(logical_and(v, expand_mask(cx, as(v)))) } } == zero_splat;
      }
    }
    else
    {
      return !any.behavior(current_api, opts, v);
    }
  }
}
