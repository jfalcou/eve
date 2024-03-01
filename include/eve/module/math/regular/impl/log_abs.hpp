//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/regular/log.hpp>

namespace eve::detail
{
  template<typename T, callable_options O>
  EVE_FORCEINLINE constexpr decltype(eve::abs(T()))
  log_abs_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
  {
    return eve::log(eve::abs(x));
  }
}
