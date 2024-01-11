//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{

  template<typename T, callable_options O>
  constexpr T
  log_gamma_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      auto aa0 = if_else(a0 == minf(as(a0)) || is_lez(signgam(a0)), allbits, a0);
      return log_abs_gamma(aa0);
    }
    else return apply_over(log_gamma, a0);
  }
}
