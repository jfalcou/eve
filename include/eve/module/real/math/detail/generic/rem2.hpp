//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/overload.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/two_prod.hpp>

namespace eve::detail
{
  template <floating_real_value T>
  EVE_FORCEINLINE auto  rem2(T const &x) noexcept
  {
    T xi = nearest(x+x);
    T x_2 = fma(xi, mhalf(eve::as<T>()), x);
    auto xr = x_2*pi(eve::as<T>());
    auto dxr =  zero(eve::as(xr));
    return kumi::make_tuple(quadrant(xi), xr, dxr);
  }
}

