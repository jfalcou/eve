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
                two_sqr_(EVE_SUPPORTS(cpu_), const T &a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto [hi, lo] = two_split(a);
    T r           = sqr(a);
    T err         = ((sqr(hi) - r) + 2 * hi * lo) + sqr(lo);
    if constexpr( eve::platform::supports_invalids ) err = if_else(is_not_finite(r), eve::zero, err);
    return {r, err};
  }
  else return apply_over2(two_sqr, a);
}
}
