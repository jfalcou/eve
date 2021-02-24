//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/cyl_bessel_y.hpp>
#include <eve/function/derivative.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/converter.hpp>


namespace eve::detail
{

  template<floating_real_value T, integral_real_value N>
  EVE_FORCEINLINE constexpr T cyl_bessel_y_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  {
    using elt_t = element_type_t<T>;
    return -cyl_bessel_y(inc(n), x)+cyl_bessel_y(n, x)*to_<elt_t>(n)/x;
//    return average(cyl_bessel_y(dec(n), x), -cyl_bessel_y(inc(n), x));//is it better ?
  }
}
