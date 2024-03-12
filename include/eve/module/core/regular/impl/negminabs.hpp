//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/regular/minus.hpp>
#include <eve/module/core/regular/minabs.hpp>

namespace eve::detail
{
  template<typename T0, typename T1, typename... Ts, callable_options O>
  EVE_FORCEINLINE constexpr common_value_t<T0, T1, Ts...>
  negminabs_(EVE_REQUIRES(cpu_), O const & o, T0 a0, T1 a1, Ts... as) noexcept
  {
    return eve::minus(minabs[o](a0, a1, as...));
  }
}
