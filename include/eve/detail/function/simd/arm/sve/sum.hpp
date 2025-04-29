//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/remove_garbage.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE T sum_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> v) noexcept
    requires (sve_abi<abi_t<T, N>> && !O::contains(splat2))
  {
    using C = rbr::result::fetch_t<condition_key, O>;

    // s/uaddv is constly, for small lanes count the "scalar" approach is faster
    if constexpr (std::same_as<C, ignore_none_> && (N::value <= 2))
    {
      T sum = v.get(0);

      for_<1, 1, N::value>([&](auto i)
      {
        sum += v.get(i);
      });

      return sum;
    }
    else
    {
      auto cx = opts[condition_key];
  
      logical<wide<T, N>> m;
  
      if constexpr (relative_conditional_expr<C>) m = sve_true(cx, as<logical<wide<T, N>>>{});
      else                                        m = remove_garbage(expand_mask(cx, as<logical<wide<T, N>>>{}));
  
      return svaddv(m, v);
    }
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> sum_(EVE_REQUIRES(sve_), O const& opts, wide<T, N> v) noexcept
    requires (sve_abi<abi_t<T, N>> && O::contains(splat2))
  {
    // Allows for a single mov to splat the result if N::value < expected_cardinal_v<T>
    return wide<T, N>{ wide<T>{ sum[opts.drop(splat2)].retarget(current_api, v) } };
  }
}
