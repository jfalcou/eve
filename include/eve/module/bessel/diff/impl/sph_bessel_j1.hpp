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

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_j1_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      //−2sin(x)/x^3+2cos(x)/x^2+sin(x)/x
      auto [s, c] = sincos(x);
      auto sq =  sqr(x);
      return if_else(x == inf(as(x))
                    , zero
                    , if_else(abs(x) < eps(as(x))
                             , inf(as(x))
                             , fma(sq-2, s, 2*x*c)/(sq*x)
                             )
                    );
    }
    else return apply_over(diff(sph_bessel_j1), x);
  }
}
