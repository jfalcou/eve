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

namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_yn_(EVE_SUPPORTS(cpu_)
                                            , diff_type<1> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      auto nph = convert(n, as<element_type_t<T>>())+half(as(x));
      auto d = rsqrt(2*x*inv_pi(as(x)));
      return if_else( abs(x) < eps(as(x))
                    , inf(as(x))
                    , (cyl_bessel_yn(nph, x)*mhalf(as(x))/x+diff(cyl_bessel_yn)(nph, x))*d
                    );
    }
    else return apply_over(diff(sph_bessel_yn), n, x);
   }
}
