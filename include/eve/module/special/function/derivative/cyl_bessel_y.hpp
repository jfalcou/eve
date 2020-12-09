//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
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

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr T cyl_bessel_y_(EVE_SUPPORTS(cpu_)
                                  , derivative_type<1> const &
                                  , T const &x) noexcept
  {
    using elt_t = element_type_t<T>;
    return -cyl_bessel_y(inc(n), x)+cyl_bessel_y(n, x)*to_<elt_t>(n)/x;
//    return average(cyl_bessel_y(dec(n), x), -cyl_bessel_y(inc(n), x));//is it better ?
  }
}
