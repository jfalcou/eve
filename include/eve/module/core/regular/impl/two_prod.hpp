//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_not_finite.hpp>
#include <eve/module/core/regular/two_split.hpp>
#include <eve/arch/platform.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE kumi::tuple<T, T>
                two_prod_(EVE_SUPPORTS(cpu_), const T &a, const T &b) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto r0 = a * b;
    auto r1 = numeric(fms)(a, b, r0);
    return {r0, r1};
  }
  else return apply_over2(two_prod, a, b);
}
}
