//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/is_equal.hpp>
#include <eve/module/core/regular/logical_not.hpp>

namespace eve::detail
{
  template<callable_options O, arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE logical<wide<T, N>>
  is_not_equal_(EVE_REQUIRES(neon128_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires arm_abi<abi_t<T, N>>
  {
    if constexpr (O::contains_any(definitely, numeric)) return is_not_equal.behavior(cpu_{}, opts, a, b);
    else return logical_not(is_equal.behavior(current_api, opts, a, b));
  }
}
