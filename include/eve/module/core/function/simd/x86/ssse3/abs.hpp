//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste 
  Copyright 2019 Joel FALCOU
 
  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_SSSE3_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_SSSE3_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/bitwise_notand.hpp>
#include <eve/function/bitwise_xor.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/function/add.hpp>
#include <eve/function/shr.hpp>
#include <type_traits>
#include <cassert>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Basic
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> abs_(EVE_SUPPORTS(ssse3_),
                                       wide<T, N, sse_> const &v) noexcept
  {
    using t_t =  wide<T, N, avx_>; 
    if constexpr(std::is_arithmetic_v<T>)
    {
      if constexpr(std::is_integral_v<T>)
      {
        constexpr bool issigned = std::is_signed_v<T>; 
        if constexpr(!issigned) return v;
        if constexpr(issigned && sizeof(T) == 1) return _mm_abs_epi8(v);
        if constexpr(issigned && sizeof(T) == 2) return _mm_abs_epi16(v);
        if constexpr(issigned && sizeof(T) == 4) return _mm_abs_epi32(v);
        if constexpr(issigned && sizeof(T) == 8)
        {
          t_t s = eve::shr(v, sizeof(T)*8-1);
          return  bitwise_xor(add(v, s), s);
          // is it better here than :  map(eve::abs, v);
          // ie 2 scalar abs ?
          //       return map(eve::abs, v);
        }
      }
      if constexpr(std::is_floating_point_v<T>) return bitwise_notand(Mzero<t_t>(),v); 
    }
    else
    {
      static_assert(std::is_arithmetic_v<T>,
                    "[ eve::abs] - No support for logical values");
    }
  }   
}



#endif
