//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_REDUCE_FAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_REDUCE_FAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/nearest.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  EVE_FORCEINLINE auto  reduce_fast_(EVE_SUPPORTS(cpu_)
                                         , float const &x) noexcept
  {
    /* Reduce range of x to within PI/2 with abs (x) <  255*pi/4. */
    static constexpr double pi_inv = 0x1.45F306DC9C883p+23;
    double r = x * pi_inv;
    int32_t  n = ((int32_t)r + 0x800000) >> 24;
    double xr = x - n * Pio_2<double>();
    float dxr = xr-float(xr); 
    float fn =  n&3; 
    return std::make_tuple(fn, float(xr), dxr); 
  }

   EVE_FORCEINLINE auto  reduce_fast_(EVE_SUPPORTS(cpu_)
                                      , double const &x) noexcept
  {
    /* Reduce range of x to within PI/2 with abs (x) < 105414350.  */
    static const double mp1 = -0x1.921FB58000000p0;   /*  -1.5707963407039642      */
    static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
    static const double mp3 = -0x1.CB3B399D747F2p-55; /* -4.9789962505147994e-17  */
    auto xn =  nearest(x*Twoopi<double>());
    auto y  =  fma(xn, mp2, fma(xn, mp1, x)); 
    auto n = quadrant(xn); 
    auto da = xn * mp3;
    auto a = y - da;
    da = (y - a) - da;
    return std::make_tuple(n, a, da); 
  }
}


#endif
