//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/cyl_bessel_y0.hpp>
#include <eve/function/cyl_bessel_y.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/average.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_y1_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return average(cyl_bessel_y0(x), -cyl_bessel_y(2, x));
  }
}
