//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/inf.hpp>
#include <eve/module/core/regular/rec.hpp>
#include <eve/module/core/regular/sqrt.hpp>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr T rsqrt_(EVE_REQUIRES(cpu_), O const& , T const& a0) noexcept
  {
    if constexpr( scalar_value<T> )
      return a0 ? rec[pedantic](eve::sqrt(a0)) : inf(eve::as(a0));
    else
      return map_pt(as<T>{}, rsqrt, a0);
  }
}
