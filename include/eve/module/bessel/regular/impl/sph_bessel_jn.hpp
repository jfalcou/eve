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
#include <eve/module/bessel/regular/cyl_bessel_jn.hpp>

namespace eve::detail
{
  template<value I, floating_value T>
  EVE_FORCEINLINE auto sph_bessel_jn_(EVE_SUPPORTS(cpu_), I nu, T x) noexcept
  {
    using elt_t = element_type_t<T>;
    if constexpr(integral_value<I>) return sph_bessel_jn(convert(nu, as<elt_t>()), x);
    else
      return if_else( abs(x) < eps(as(x))
                    , if_else(is_eqz(nu), one(as(x)), zero)
                    , cyl_bessel_jn(nu+half(as(nu)), x)*rsqrt(2*x*invpi(as(x)))
                    );
  }
}
