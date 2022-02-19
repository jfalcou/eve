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
#include <eve/module/bessel/diff/cyl_bessel_jn.hpp>


namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T sph_bessel_jn_(EVE_SUPPORTS(cpu_)
                                            , diff_type<1> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      EVE_ASSERT(all(is_gez(n) && is_flint(n)), "diff(sph_bessel_jn) : some orders are non integral positive");
      EVE_ASSERT(all(is_nltz(x)),               "diff(sph_bessel_jn) : some x are negative");
      auto nph = convert(n, as<element_type_t<T>>())+half(as(x));
      auto d = rsqrt(2*x*invpi(as(x)));
      return if_else( abs(x) < eps(as(x))
                    ,  if_else(is_eqz(n),  zero, inf(as(x)))
                    , (cyl_bessel_jn(nph, x)*mhalf(as(x))/x+diff(cyl_bessel_jn)(nph, x))*d
                    );
    }
    else return apply_over(diff(sph_bessel_jn), n, x);
   }
}
