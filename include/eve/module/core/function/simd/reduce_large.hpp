//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_REDUCE_LARGE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_REDUCE_LARGE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/reduce_fast.hpp> 
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

  template < typename N, typename ABI>
  EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
                                     , wide<float, N, ABI>const &x) noexcept
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
    using ui_t =   wide<uint32_t, N, ABI>
    static const double pi63 = 0x1.921FB54442D18p-62;/* 2PI * 2^-64.  */
//    auto [sn, sr] =  reduce_fast(x); 
//    if (all(x <= 120.0f)) return std::tuple<float, float>(sn, sr); 
    auto xi =  bitwise_cast(x, as_<ui_t>())); 
    const uint32_t *arr = &__inv_pio4[(xi >> 26) & 15u];
    auto shift = (xi >> 23) & 7;
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
    return if_else(x <= 120.0f,
                   reduce_fast(x),
                   std::tuple<float, float>(static_cast<float>(n), static_cast<float>(xx * pi63));
                   }
      
  }
}

#endif
 
