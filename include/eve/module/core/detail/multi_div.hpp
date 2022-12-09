//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/concept/value.hpp>
#include <eve/traits/common_value.hpp>

namespace eve::detail
{
  template<decorator D, value T0, value T1, value... Ts>
  auto
  div_(EVE_SUPPORTS(cpu_), D const& d, T0 a0, T1 a1, Ts... args) noexcept
  -> common_value_t<T0, T1, Ts...>
  {
    using r_t = common_value_t<T0, T1, Ts...>;
    r_t that(a1);
    that = d(mul)(that, r_t(args)...);
    EVE_ASSERT(eve::all(is_nez(that)), "[eve] D()(div) - 0/0 is undefined");
    return (D()(div))(r_t(a0), that);
  }
}
