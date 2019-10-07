//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_REDUCE_FAST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_REDUCE_FAST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/bitwise_and.hpp>
#include <eve/function/fnma.hpp>
#include <eve/function/quadrant.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/fnma.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/function/wide_cast.hpp>
#include <eve/function/rem_pio2_medium.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
  template < typename N,  typename ABI>
  EVE_FORCEINLINE auto  reduce_fast_(EVE_SUPPORTS(cpu_)
                                    , wide < float, N, ABI> const &x) noexcept
  {
//    static constexpr double pi_inv = 0x1.45F306DC9C883p+23;
    using t_t = wide < float, N, ABI>;        
    using d_t = wide < double, N>;
    d_t dx =wide_cast(x, as<double>()); 
    d_t n  =  eve::nearest(dx * Twoopi<double>()); //pi_inv);
//    std::cout << "n " << n << std::endl; 
// //     auto  n = wide_cast((wide_cast(r, as(int32_t()))+ 0x800000
// //                         ) >> 24
// //                        , as(double()));
     d_t z = fnma(n,  Pio_2<double>(), dx); 
// //    auto xr = wide_cast(x - n * Pio_2<double>(), as<float>());
     auto xr = wide_cast(z,as<float>()); 
     auto fn = wide_cast(quadrant(n),as<float>());
//    return std::tuple<t_t, t_t>(t_t(0), t_t(0)); 
    return std::tuple<t_t, t_t>{fn, xr}; 
  }
  
  template < typename N,  typename ABI>
  EVE_FORCEINLINE auto  reduce_fast_(EVE_SUPPORTS(cpu_)
                                    , wide < double, N, ABI> const &x) noexcept
  {
    return rem_pio2_medium(x);
  }
  
  
//   template < typename N,  typename ABI>
//   EVE_FORCEINLINE auto  reduce_fast_(EVE_SUPPORTS(cpu_)
//                                          , wide<float, N, ABI> const &x) noexcept
//   {
//     static constexpr double pi_inv = 0x1.45F306DC9C883p+23;
//     auto dblx = wide_cast<double>(x); 
//     auto r = dblx * pi_inv;
//     auto  n = wide_cast<float>(wide_cast<int32_t>(r) + 0x800000) >> 24);
//     float xr = x - n * Pio_2<double>();
//     float fn =  n&3; 
//     return std::tuple<float, float>{fn, xr}; 
//   }
}

#endif
