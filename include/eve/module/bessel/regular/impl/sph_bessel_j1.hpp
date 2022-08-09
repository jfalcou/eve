//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
sph_bessel_j1_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return if_else((abs(x) <= eps(as(x))) || (x == inf(as(x))), zero, (sinc(x) - cos(x)) / x);
}
}
