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

namespace eve::detail
{
template<ordered_value T>
EVE_FORCEINLINE auto
rem2(T const& x) noexcept
{
  T    xi  = nearest(x + x);
  T    x_2 = fma(xi, mhalf(eve::as<T>()), x);
  auto xr  = x_2 * pi(eve::as<T>());
  auto dxr = zero(eve::as(xr));
  return kumi::make_tuple(quadrant(xi), xr, dxr);
}
}
