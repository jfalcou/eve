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

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/mhalf.hpp>

#include <type_traits>


// TODO revision to:
// pedantic will call pedantic fma and fnma
// and the no extrapolation will be obtained through named parameter no_extrap = t


namespace eve::detail
{
  template<  floating_real_value X1
           , floating_real_value X2
           , floating_real_value Y1,
           , floating_real_value Yp1
           , floating_real_value Y2
           , floating_real_value Yp2
           , floating_real_value X>
  EVE_FORCEINLINE auto hermite_interp_(EVE_SUPPORTS(cpu_)
                                      , X1 const &x1
                                      , X2 const &x2           
                                      , Y1 const &y1
                                      , Yp1 const &yp1
                                      , Y2 const &y2
                                      , Yp2 const&yp2
                                      , X const &x) noexcept
  requires compatible_values<X, X1> && compatible_values<X, X2> &&
           compatible_values<X, Y1> && compatible_values<X, Yp1>&&
           compatible_values<X, Y2> && compatible_values<X, Yp2>
  {
    auto l = x2-x1;
    auto t = (x-x1)/l;
    return arithmetic_call(cbrp, y1, l*y1p, y2, l*y2p, t);
  }
}
