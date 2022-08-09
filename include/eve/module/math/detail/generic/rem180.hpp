//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>
#include <eve/module/math/regular/quadrant.hpp>
#include <eve/module/math/regular/div_180.hpp>

namespace eve::detail
{
  template <floating_real_value T>
  EVE_FORCEINLINE auto  rem180(T x) noexcept
  {
    T xi = nearest(2*div_180(x));
    x = fma(xi, T(-90), x);
    T fn = quadrant(xi);
    T xr = x;
    auto tst = x >= 45;
    xr = if_else(tst, xr-T(45), xr);
    tst = xr >= 45;
    xr = if_else(tst, xr-T(45), xr);
    tst = xr >= 45;
    xr = if_else(tst, x-T(45), xr);
    xr = div_180(xr) *pi(as(xr));
    return kumi::make_tuple(fn, xr, zero(as(xr)));
  }
}
