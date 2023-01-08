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
#include <eve/module/core/regular/is_finite.hpp>

namespace eve::detail
{
template<floating_ordered_value T>
EVE_FORCEINLINE kumi::tuple<T, T>
                two_sub_(EVE_SUPPORTS(cpu_)
                              , const T &a
                              , const T &b) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    T s = a - b;
    T bb = s - a;
    T err = (a - (s - bb)) - (b + bb);
    if constexpr( eve::platform::supports_infinites )
      err =  if_else(is_infinite(s), eve::zero, err);
    return {s, err};
  }
  else return apply_over2(two_sub, a, b);
}
}
