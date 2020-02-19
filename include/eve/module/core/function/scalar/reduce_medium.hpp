//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_MEDIUM_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_MEDIUM_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/rem_pio2_cephes.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/constant/constant.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>
#include <eve/function/prev.hpp>
#include <eve/function/ulpdist.hpp>

namespace eve::detail
{
  // x < 281474976710656
  EVE_FORCEINLINE auto  reduce_medium_(EVE_SUPPORTS(cpu_)
                                      , double const &x) noexcept
  {
    static const double mp1 = -0x1.921FB58000000p0;   /* -1.5707963407039642      */
    static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
    static const double pp3 = -0x1.CB3B398000000p-55; /* -4.9789962314799099e-17  */
    static const double pp4 =  0x1.d747f23e32ed7p-83; /*  1.9034889620193266e-25  */
    
    double xn =  nearest(x*Twoopi<double>());
    double xn1 = (xn + 8.0e22) - 8.0e22;
    double xn2 = xn - xn1;
    double y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, x)))); 
    double n = quadrant(xn); //  int4 n = v.i[LOW_HALF] & 3;
    double da = xn1 * pp3;
    double t = y - da;
    da = (y - t) - da;
    da = fma(xn, pp4, fnma(xn2, pp3, da));
    double a = t + da;
    da = (t - a) + da;
    return std::make_tuple(n, a, da); 
  }
  
  /* float use  up to 1.0e15*/
  EVE_FORCEINLINE auto  reduce_medium_(EVE_SUPPORTS(cpu_)
                                      , float const &x) noexcept
  {
    static const double mp1 = -0x1.921FB58000000p0;   /* -1.5707963407039642      */
    static const double mp2 =  0x1.DDE973C000000p-27; /*  1.3909067564377153e-08  */
    static const double pp3 = -0x1.CB3B398000000p-55; /* -4.9789962314799099e-17  */
    static const double pp4 =  0x1.d747f23e32ed7p-83; /*  1.9034889620193266e-25  */
    
    double xn =  nearest(x*Twoopi<double>());
    double xn1 = (xn + 8.0e22) - 8.0e22;
    double xn2 = xn - xn1;
    double y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, double(x))))); 
    float n = quadrant(xn);
    double da = xn1 * pp3;
    double t = y - da;
    da = (y - t) - da;
    da = fma(xn, pp4, fnma(xn2, pp3, da));
    double a = t + da;
    da = (t - a) + da;
    float fa = a;
    float dfa = (a-double(fa))+da;
    if (eve::abs(fa) > Pio_4<float>())
    {
      auto [n1, fa1, fa1c] = eve::reduce_fast(fa);
      n = (int(n+n1)&3); 
      return std::make_tuple(n, fa1, 0.0f); 
    }
    return std::make_tuple(n, fa, dfa); 
  }

}

#endif
