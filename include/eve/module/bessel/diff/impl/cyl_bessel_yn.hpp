//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/derivative.hpp>
#include <eve/module/math.hpp>
#include <eve/module/bessel/regular/cyl_bessel_yn.hpp>

namespace eve::detail
{

  template<real_value I, floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_yn_(EVE_SUPPORTS(cpu_)
                                            , diff_type<1> const &
                                            , I n
                                            , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      return average(cyl_bessel_yn(dec(n), x), -cyl_bessel_yn(inc(n), x));
    }
    else return apply_over(diff(cyl_bessel_yn), n, x);
   }
}
