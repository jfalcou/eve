//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_COS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                            , eve::wide<T,N,ABI> const &a0) noexcept
  {
    return regular_(cos)(a0); 
  }

  template<typename T,  typename N,  typename ABI>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                           , restricted_type const &     
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      auto pi2_16 = static_cast<T>(0.61685027506808491367715568749226); 
      auto x2 = sqr(a0); 
      tst = is_not_less_equal(x2, pi2_16); 
//      EVE_ASSERT(!all(test), "Restricted cos called with arg magnitude greater than Pi/4"); 
      return if else(tst, Allbits(as(a0)), cos_eval(x)); 
    }
    else
    {
      static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
    }   
  }

  template<typename T,  typename N,  typename ABI,  typename TAG>
  EVE_FORCEINLINE auto cos_(EVE_SUPPORTS(cpu_)
                           , TAG const &     
                           , eve::wide<T,N,ABI> const &a0) noexcept
  {
    static_assert(std::is_floating_point_v<T>, "still not implemented");
    return T{}; 
//     if constexpr(std::is_floating_point_v<T>)
//     {
//     }
//     else
//     {
//       static_assert(std::is_floating_point_v<T>, "[eve::cos scalar ] - type is not an IEEEValue"); 
//     }   
  }
}

#endif
