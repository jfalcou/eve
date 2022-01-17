//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/math.hpp>
#include <eve/module/bessel/regular/cyl_bessel_k0.hpp>
#include <eve/module/bessel/regular/cyl_bessel_kn.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_k1_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T const &x) noexcept
  {
    return -average(cyl_bessel_kn(T(2), x), cyl_bessel_k0(x));
  }
}
