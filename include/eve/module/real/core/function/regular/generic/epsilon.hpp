//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/dist.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/next.hpp>

namespace eve::detail
{
  template<real_value T> EVE_FORCEINLINE constexpr T epsilon_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto aa = abs(a);
      return if_else(is_nan(a), allbits, dist(aa, next(aa)));
    }
    else
    {
      return apply_over(eve::epsilon, a);
    }
  }
}
