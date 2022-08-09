//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr T rsqrt_(EVE_SUPPORTS(cpu_), D const &, T a0) noexcept
  {
    return rsqrt(a0);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T rsqrt_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    if constexpr( scalar_value<T> )
    {
      return a0 ? rec(eve::sqrt(a0)) : inf(eve::as(a0));
    }
    else if constexpr( has_aggregated_abi_v<T> )
    {
      return aggregate(eve::rsqrt, a0);
    }
    else
    {
      return map(rsqrt, a0);
    }
  }
}
