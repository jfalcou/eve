//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/maxabs.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  negmaxabs_(EVE_REQUIRES(cpu_), O const& o, T0 a0, T1 a1, Ts... as) noexcept
  {
    return eve::minus(maxabs[o](a0, a1, as...));
  }
}
