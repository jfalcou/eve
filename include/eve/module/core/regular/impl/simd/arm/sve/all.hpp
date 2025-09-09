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

namespace eve::detail
{
  template<callable_options O, scalar_value T, typename N>
  EVE_FORCEINLINE auto all_(EVE_REQUIRES(sve_), O const& opts, logical<wide<T, N>> v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    using C = rbr::result::fetch_t<condition_key, O>;
    auto cx = opts[condition_key];

    if constexpr (O::contains(splat))
    {
      // two constructors to allow the compiler to understand that we want to splat but still communicate the "real"
      // size of the operands to eve::equal
      auto size_splat = wide<T, N> { wide<T> { N::value } };

      return logical<wide<T, N>> { false };
      // if constexpr (C::is_complete)
      // {
      //   if constexpr (C::is_inverted) return wide<T, N> { wide<T> { count_true(v) } } == size_splat;
      //   else                          return logical<wide<T, N>> { true };
      // }
      // else if constexpr (relative_conditional_expr<C>)
      // {
      //   return wide<T, N> { wide<T> { count_true[cx](v) } } == wide<T, N> { wide<T> { cx.count(as(v)) } };
      // }
      // else
      // {
      //   return wide<T, N> { wide<T> { count_true(logical_ornot(v, expand_mask(cx, as(v)))) } } == size_splat;
      // }
    }
    else
    {
      if constexpr( C::is_complete )
      {
        if constexpr( C::is_inverted )  return count_true(v) == N::value;
        else                            return true;
      }
      else
      {
        if constexpr (relative_conditional_expr<C>) return count_true[cx](v) == cx.count(as(v));
        else                                        return count_true(logical_ornot(v, expand_mask(cx, as(v)))) == N::value;
      }
    }
  }
}
