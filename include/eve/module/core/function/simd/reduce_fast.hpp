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
#include <eve/function/trunc.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/constant/twoopi.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <tuple>

namespace eve::detail
{
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
