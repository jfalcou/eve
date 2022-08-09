//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_value T>
EVE_FORCEINLINE auto
sph_bessel_y1_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return if_else(x == inf(as(x)), zero, -cos(x) / sqr(x) - sinc(x));
}
}
