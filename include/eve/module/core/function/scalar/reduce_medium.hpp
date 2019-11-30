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
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/function/rem_pio2_cephes.hpp>
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
//  double y = ((((x + xn1 * mp1) + xn1 * mp2) + xn2 * mp1) + xn2 * mp2);
  double y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, x)))); 
  double n = quadrant(xn); //  int4 n = v.i[LOW_HALF] & 3;
  double da = xn1 * pp3;
  double t = y - da;
         da = (y - t) - da;
         da = fma(xn, pp4, fnma(xn2, pp3, da));
  double a = t + da;
         da = (t - a) + da;
         
 //    double    mp1 = Constant<double, 0x3FF921FB58000000ULL>();  /* 1.5707963407039642     */
//     double    mp2 = Constant<double, 0xBE4DDE973C000000ULL>();  /*-1.3909067675399456e-08 */
//     double    pp3 = Constant<double, 0xBC8CB3B398000000ULL>();  /*-4.9790e-17             */
//     double    pp4 = Constant<double, 0xbacd747f23e32ed7ULL>();  /*-1.9035e-25             */
//     double  hpinv = Constant<double, 0x3FE45F306DC9C883ULL>();  
//     double  toint = Constant<double, 0x4338000000000000ULL>(); 
    
//     double t = (x * hpinv + toint);
//     double xn = t - toint;
// //    xn =  nearest(x*Twoopi<double>()); 
//     double y = (x - xn * mp1) - xn * mp2;
//     double n = quadrant(xn); 
//     double t1 = xn * pp3;
//     double t2 = y - t1;
//     double da = (y - t2) - t1;
    
//     t1 = xn * pp4;
//     double a = t2 - t1;
//     da += (t2 - a) - t1;

    return std::tuple<double, double, double>(n, a, da); 
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
//  double y = ((((x + xn1 * mp1) + xn1 * mp2) + xn2 * mp1) + xn2 * mp2);
  double y = fma(xn2, mp2, fma(xn2, mp1, fma(xn1, mp2, fma(xn1, mp1, double(x))))); 
  double n = quadrant(xn); //  int4 n = v.i[LOW_HALF] & 3;
  double da = xn1 * pp3;
  double t = y - da;
         da = (y - t) - da;
         da = fma(xn, pp4, fnma(xn2, pp3, da));
  double a = t + da;
         da = (t - a) + da;

 //         double    mp1 = Constant<double, 0x3FF921FB58000000ULL>();  /* 1.5707963407039642     */
//     double    mp2 = Constant<double, 0xBE4DDE973C000000ULL>();  /*-1.3909067675399456e-08 */
//     double    pp3 = Constant<double, 0xBC8CB3B398000000ULL>();  /*-4.9790e-17             */
//     double    pp4 = Constant<double, 0xbacd747f23e32ed7ULL>();  /*-1.9035e-25             */
// //     double  hpinv = Constant<double, 0x3FE45F306DC9C883ULL>();  
// //     double  toint = Constant<double, 0x4338000000000000ULL>(); 
    
// //     double t = (x * hpinv + toint);
// //     double xn = t - toint;
//     xn =  nearest(x*Twoopi<double>()); 
//     double y = (x - xn * mp1) - xn * mp2;
//     double n = quadrant(xn); 
//     double t1 = xn * pp3;
//     double t2 = y - t1;
//     double da = (y - t2) - t1;
    
//     t1 = xn * pp4;
//     double a = t2 - t1;
//     da += (t2 - a) - t1;

    float fa = a;
    float dfa = (a-double(fa))+da;
//     if (fa == Pio_4<float>())
//     {
//       fa =  -fa; n = (int(n)+1)&3;
//     }
    
//     std::cout << "fa  "  << fa  << std::endl;
//     std::cout << "abs(fa) "<< eve::abs(fa)  << std::endl;
//    std::cout << "dist " << ulpdist(abs(fa) , Pio_4<float>()) << std::endl;
//     std::abort(); 
    if (eve::abs(fa) > Pio_4<float>())
    {
//      std::cout << "icitte" << fa << std::endl; 
      auto [n1, fa1, fa1c] = eve::rem_pio2_cephes(fa);
//      std::cout << "fa1 " << fa1 << std::endl;
//      std::cout << "fa  " << fa  << std::endl;     
       
      n = float(int(n+n1)&3); 
      return std::tuple<float, float, float>(n, fa1, 0.0f); 
    }
    
    return std::tuple<float, float, float>(n, fa, dfa); 
  }

}

#endif
