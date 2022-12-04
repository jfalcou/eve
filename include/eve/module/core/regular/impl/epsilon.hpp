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
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/next.hpp>

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE constexpr T
epsilon_(EVE_SUPPORTS(cpu_), T const& a) noexcept
{
  if constexpr( has_native_abi_v<T> )
  {
    auto aa = abs(a);
    return if_else(is_nan(a), allbits, dist(aa, next(aa)));
  }
  else { return apply_over(eve::epsilon, a); }
}
}
