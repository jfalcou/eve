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
#include <eve/function/gather.hpp>
#include <eve/function/all.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/bitwise_or.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/shr.hpp>
#include <eve/function/shl.hpp>
#include <eve/function/wide_cast.hpp>
#include <eve/wide.hpp>
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

//   template < typename N, typename ABI>
//   EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
//                                      , wide<float, N, ABI> const &x) noexcept
//   {
//     // Table with 4/PI to 192 bit precision.  To avoid unaligned accesses
//     //   only 8 new bits are added per entry, making the table 4 times larger.  
    
//     using t_t =  wide<float, N, ABI>;
//     using ui_t =  wide<uint32_t, N, ABI>;
//     constexpr auto alg = ui_t::static_alignment;
//     alignas(alg) constexpr const uint32_t __inv_pio4[24] =
//       {
//         0xa2,       0xa2f9,   0xa2f983,   0xa2f9836e,
//         0xf9836e4e, 0x836e4e44, 0x6e4e4415, 0x4e441529,
//         0x441529fc, 0x1529fc27, 0x29fc2757, 0xfc2757d1,
//         0x2757d1f5, 0x57d1f534, 0xd1f534dd, 0xf534ddc0,
//         0x34ddc0db, 0xddc0db62, 0xc0db6295, 0xdb629599,
//         0x6295993c, 0x95993c43, 0x993c4390, 0x3c439041
//       };
//     constexpr const double pi63 = 0x1.921FB54442D18p-62;/* 2PI * 2^-64.  */
//     auto [sn, sr] =  reduce_fast(x);
//     auto xle120 = x <= 120.0f; 
//     if (all(xle120)) return std::tuple<t_t, t_t>(sn, sr); 
//     auto xi =  bitwise_cast(x, as_<ui_t>());
//     auto index =  bitwise_and(shr(xi, 26), 15); 
// //    auto arr0 = gather(&__inv_pio4[0], index);
//     auto arr4 = wide_cast(gather(&__inv_pio4[0], index+4), as<uint64_t>());
//     auto arr8 = wide_cast(gather(&__inv_pio4[0], index+8), as<uint64_t>()); 
//      auto arr0 = gather(eve::as_aligned<alg>(&__inv_pio4[0]), index);
// //     auto arr4 = wide_cast(gather(eve::as_aligned<alg>(&__inv_pio4[0]), index+4), as<uint64_t>());
// //     auto arr8 = wide_cast(gather(eve::as_aligned<alg>(&__inv_pio4[0]), index+8), as<uint64_t>()); 
//     auto shift = bitwise_and(shr(xi, 23), 7);
    
//     xi = bitwise_or(bitwise_and(xi, 0xffffff), 0x800000); 
//     xi = shl(xi, shift);
//     auto xi64 = wide_cast(xi, as<uint64_t>());
    
//     auto res0 = wide_cast(xi * arr0, as<uint64_t>());
//     auto res1 = xi64 * arr4;
//     auto res2 = xi64 * arr8;
//     res0 = bitwise_or(shr(res2, 32), shl(res0, 32));
//     res0 += res1;
    
//     auto n = shr((res0 + (1ULL << 61)), 62);
//     res0 -= n << 62;
//     auto xx =  wide_cast(wide_cast(res0, as<int64_t>()), as<double>());
    
//     return std::tuple<t_t, t_t, t_t>(if_else(xle120, sn, wide_cast(n, as<float>()))
//                                     , if_else(xle120, sr, wide_cast(xx * pi63, as<float>()))
//                                     , t_t(0)); 
//   }

  template <typename N, typename ABI>
  EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
                                     , wide<double, N, ABI> const &x) noexcept
  {
    double    mp1 = Constant<double, 0x3FF921FB58000000ULL>();  /* 1.5707963407039642     */
    double    mp2 = Constant<double, 0xBE4DDE973C000000ULL>();  /*-1.3909067675399456e-08 */
    double    pp3 = Constant<double, 0xBC8CB3B398000000ULL>();  /*-4.9790e-17             */
    double    pp4 = Constant<double, 0xbacd747f23e32ed7ULL>();  /*-1.9035e-25             */
    using t_t = wide<double, N, ABI>; 
    
//     T t = (x * hpinv + toint);
//     T xn = t - toint;
    auto xn =  nearest(x*Twoopi<double>()); 
    auto y = (x - xn * mp1) - xn * mp2;
    auto n = quadrant(xn); 
    auto t1 = xn * pp3;
    auto t2 = y - t1;
    auto da = (y - t2) - t1;
    
    t1 = xn * pp4;
    auto a = t2 - t1;
    da += (t2 - a) - t1;
    
    return std::tuple<t_t, t_t, t_t>(n, a, da); 
  }

  template <typename N, typename ABI>
  EVE_FORCEINLINE auto  reduce_large_(EVE_SUPPORTS(cpu_)
                                     , wide<float, N, ABI> const &x) noexcept
  {
    using t_t = wide<float, N, ABI>; 
    auto [n, xr, dxr] = reduce_large(wide_cast(x, as<double>()));
    return std::tuple<t_t, t_t, t_t>(wide_cast(n, as<float>())
                                          , wide_cast(xr, as<float>())
                                          , wide_cast(dxr, as<float>())); 
  }
 
}


#endif
 
