//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/module/core/regular/mul.hpp>

namespace eve::detail
{
template<decorator D, real_value T0, real_value T1, real_value... Ts>
common_compatible_t<T0, T1, Ts...>
mul_(EVE_SUPPORTS(cpu_), D const& d, T0 a0, T1 a1, Ts... args)
{
  using r_t = common_compatible_t<T0, T1, Ts...>;
  r_t that(d(mul)(r_t(a0), r_t(a1)));
  ((that = d(mul)(that, r_t(args))), ...);
  return that;
}
}
