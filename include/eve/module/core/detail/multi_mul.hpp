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
#include <eve/concept/value.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template<decorator D, real_value T0, real_value T1, real_value... Ts>
  auto
  mul_(EVE_SUPPORTS(cpu_), D const& d, T0 a0, T1 a1, Ts... args) noexcept
  -> common_value_t<T0, T1, Ts...>
  {
    using r_t = common_value_t<T0, T1, Ts...>;
    r_t that(d(mul)(r_t(a0), r_t(a1)));
    ((that = d(mul)(that, r_t(args))), ...);
    return that;
  }
}
