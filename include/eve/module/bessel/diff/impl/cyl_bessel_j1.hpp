//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/bessel/regular/cyl_bessel_jn.hpp>
#include <eve/module/bessel/regular/cyl_bessel_j0.hpp>

namespace eve::detail
{

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_j1_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , T x) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
      using v_t =  element_type_t<T>;
      x = abs(x);
      return average(cyl_bessel_j0(x), -cyl_bessel_jn(v_t(2), x));
    }
    else return apply_over(diff(cyl_bessel_j1), x);
  }
}
