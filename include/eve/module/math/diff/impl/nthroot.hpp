//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/nthroot.hpp>

namespace eve::detail
{
  template<floating_real_value T, value N>
  EVE_FORCEINLINE constexpr T nthroot_(EVE_SUPPORTS(cpu_)
                                   , diff_type<1> const &
                                   , T x, N n) noexcept
  {
    using elt_t = element_type_t<T>;
    auto tn = convert(n, as<elt_t>());
    return nthroot(x, n)*rec(x*tn);
  }
}
