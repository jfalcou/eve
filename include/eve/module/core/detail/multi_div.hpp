//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/module/core/regular/div.hpp>
#include <eve/module/core/regular/mul.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/assert.hpp>

namespace eve::detail
{
  template<decorator D, real_value T0, real_value T1, real_value ...Ts>
  auto div_(EVE_SUPPORTS(cpu_), D const & d, T0 a0, T1 a1, Ts... args)
    requires compatible_values<T0, T1> && (compatible_values<T0, Ts> && ...)
  {
    using r_t = common_compatible_t<T0, T1, Ts...>;
    r_t that(a1);
    that = d(mul)(that,r_t(args)...);
    EVE_ASSERT(eve::all(is_nez(that)), "[eve] D()(div) - 0/0 is undefined");
    return (D()(div))(r_t(a0), that);
  }

}
