//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve::detail
{
template<floating_value T>
EVE_FORCEINLINE auto
sph_bessel_j0_(EVE_SUPPORTS(cpu_), T x) noexcept
{
  return sinc(x);
}
}