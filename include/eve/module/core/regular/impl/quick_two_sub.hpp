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
#include <eve/module/core/regular/is_infinite.hpp>
#include <eve/module/core/regular/is_not_less.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE kumi::tuple<T, T>
                quick_two_sub_(EVE_SUPPORTS(cpu_)
                              , const T &a
                              , const T &b) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    EVE_ASSERT(eve::all(is_not_less(eve::abs(a), eve::abs(b))), "|a| >=  |b| not satisfied for all elements");
    T s = a - b;
    T err =  (a - s) - b;
    if constexpr( eve::platform::supports_infinites )
      err = if_else(is_finite(s), err, zero);
    return {s, err};
  }
  else return apply_over2(quick_two_sub, a, b);
}
}
