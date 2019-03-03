//================================================================================================== 
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste
  Copyright 2019 Joel FALCOU
 
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/add.hpp>
#include <eve/function/shr.hpp>
#include <type_traits>
#include <cassert>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE wide<T, N, ABI> abs_(EVE_SUPPORTS(simd_),
                                       wide<T, N, ABI> const &v) noexcept
  {
    if constexpr(std::is_arithmetic_v<T>)
    {
      if constexpr(std::is_floating_point_v<T>)                    return bitwise_notand(Mzero<T>(),v);
      if constexpr(std::is_integral_v<T> && std::is_unsigned_v<T>) return v;
      if constexpr(std::is_signed_v<T> && std::is_signed_v<T>)
      {
        constexpr int Maxshift = sizeof(T)*8-1; 
        wide<T, N> s = eve::shr(v, Maxshift);
        return (v+s)^s;
      }
    }
    else
    {
      static_assert(std::is_arithmetic_v<T>,
                    "[ eve::abs] - No support for logical values");
    }
  }
  
  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, aggregated_> abs_(EVE_SUPPORTS(simd_),
                                               wide<T, N, aggregated_> const &v) noexcept
  {
    return aggregate(eve::abs, v);
  }
  
  // -----------------------------------------------------------------------------------------------
  // Emulation 
  template<typename T, typename N>
  EVE_FORCEINLINE auto abs_(EVE_SUPPORTS(simd_), wide<T, N, emulated_> const &v) noexcept
  {
    return map(eve::abs, v);;
  }


  
}



#endif
