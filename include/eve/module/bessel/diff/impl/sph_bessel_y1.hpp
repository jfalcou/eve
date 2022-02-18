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
#include <eve/module/bessel/regular/cyl_bessel_yn.hpp>
#include <eve/module/bessel/regular/cyl_bessel_y0.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_y1_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    auto sq = sqr(x);
    auto [s, c] = sincos(x);
    return if_else(x == inf(as(x)), zero, (-sq*c+2*x*s+2*c)/(x*sq));
  }
}
