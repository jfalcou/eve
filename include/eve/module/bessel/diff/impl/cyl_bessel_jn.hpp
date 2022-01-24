//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <eve/module/bessel/regular/cyl_bessel_jn.hpp>


namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_jn_(EVE_SUPPORTS(cpu_)
                                            , diff_type<1> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return average(cyl_bessel_jn(dec(n), x), -cyl_bessel_jn(inc(n), x));
    }
    else return apply_over(diff(cyl_bessel_jn), n, x);
   }
}
