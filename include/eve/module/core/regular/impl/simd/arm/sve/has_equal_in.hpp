//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_equal.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N, typename Pred>
  constexpr EVE_FORCEINLINE auto has_equal_in_(EVE_REQUIRES(sve2_), O const& opts, wide<T, N> x, wide<T, N> match_against, Pred op) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr (std::same_as<Pred, is_equal_t<eve::options<>>> && match(c, category::int8, category::uint8, category::int16, category::uint16))
    {
      return svmatch(sve_true<T>(), x, match_against);
    }
    else
    {
      return has_equal_in.behavior(cpu_{}, opts, x, match_against, op);
    }
  }
}
