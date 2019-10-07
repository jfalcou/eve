//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_LARGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REDUCE_LARGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/reduce_fast.hpp>
#include <eve/constant/constant.hpp>
// #include <eve/function/fnma.hpp>
// #include <eve/function/quadrant.hpp>
// #include <eve/function/nearest.hpp>
// #include <eve/function/trunc.hpp>
// #include <eve/constant/pio_2.hpp>
// #include <eve/constant/twoopi.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  //    Reduce the range of XI to a multiple of PI/2 using fast integer arithmetic.
  //    XI is a reinterpreted float and must be >= 2.0f (the sign bit is ignored).
  //    Return the modulo between -PI/4 and PI/4 and store the quadrant in NP.
  //    Reduction uses a table of 4/PI with 192 bits of precision.  A 32x96->128 bit
  //    multiply computes the exact 2.62-bit fixed-point modulo.  Since the result
  //    can have at most 29 leading zeros after the binary point, the double
  //    precision result is accurate to 33 bits.  
  
  EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
                                     , float const &x) noexcept
  {
    // Table with 4/PI to 192 bit precision.  To avoid unaligned accesses
    //   only 8 new bits are added per entry, making the table 4 times larger.  
    
    const uint32_t __inv_pio4[24] =
      {
        0xa2,       0xa2f9,   0xa2f983,   0xa2f9836e,
        0xf9836e4e, 0x836e4e44, 0x6e4e4415, 0x4e441529,
        0x441529fc, 0x1529fc27, 0x29fc2757, 0xfc2757d1,
        0x2757d1f5, 0x57d1f534, 0xd1f534dd, 0xf534ddc0,
        0x34ddc0db, 0xddc0db62, 0xc0db6295, 0xdb629599,
        0x6295993c, 0x95993c43, 0x993c4390, 0x3c439041
      };
    static const double pi63 = 0x1.921FB54442D18p-62;/* 2PI * 2^-64.  */
    if (x <= 120.0f)
    {
      return reduce_fast(x); 
    }
    else{
      auto xi =  bitwise_cast(x, as_<uint32_t>()); 
      const uint32_t *arr = &__inv_pio4[(xi >> 26) & 15];
      int shift = (xi >> 23) & 7;
      uint64_t n, res0, res1, res2;
      
      xi = (xi & 0xffffff) | 0x800000;
      xi <<= shift;
      
      res0 = xi * arr[0];
      res1 = (uint64_t)xi * arr[4];
      res2 = (uint64_t)xi * arr[8];
      res0 = (res2 >> 32) | (res0 << 32);
      res0 += res1;
      
      n = (res0 + (1ULL << 61)) >> 62;
      res0 -= n << 62;
      double xx = (int64_t)res0;
      return std::tuple<float, float, float>(static_cast<float>(n), static_cast<float>(xx * pi63), 0.0f);
    }
  }

//            mp1 = {{0x3FF921FB, 0x58000000} },
//            mp2 = {{0xBE4DDE97, 0x3C000000} },
//            mp3 = {{0xBC8CB3B3, 0x99D747F2} },
//            pp3 = {{0xBC8CB3B3, 0x98000000} },
//            pp4 = {{0xbacd747f, 0x23e32ed7} },
//          hpinv = {{0x3FE45F30, 0x6DC9C883} },
//          toint = {{0x43380000, 0x00000000} };
 
/* Reduce range of x to within PI/2 with abs (x) < 105414350.  The high part
   is written to a, the low part to da.  Range reduction is accurate to 136
   bits so that when x is large and *a very close to zero, all 53 bits of *a
   are correct.  */

  EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
                                     , double const &x) noexcept
  {
    double    mp1 = Constant<double, 0x3FF921FB58000000ULL>();  /* 1.5707963407039642     */
    double    mp2 = Constant<double, 0xBE4DDE973C000000ULL>();  /*-1.3909067675399456e-08 */
    double    pp3 = Constant<double, 0xBC8CB3B398000000ULL>();  /*-4.9790e-17             */
    double    pp4 = Constant<double, 0xbacd747f23e32ed7ULL>();  /*-1.9035e-25             */
   
//     double t = (x * hpinv + toint);
//     double xn = t - toint;
    auto xn =  nearest(x*Twoopi<double>()); 
    double y = (x - xn * mp1) - xn * mp2;
    double n = quadrant(xn); 
    double t1 = xn * pp3;
    double t2 = y - t1;
    double da = (y - t2) - t1;
    
    t1 = xn * pp4;
    double a = t2 - t1;
    da += (t2 - a) - t1;
    
    return std::tuple<double, double, double>(n, a, da); 
  }

}

#endif
