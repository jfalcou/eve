//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_ABS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_ABS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_notand.hpp>
#include <eve/forward.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<scalar_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> abs_(EVE_SUPPORTS(ssse3_)
                                       , wide<T, N, sse_> const &v) noexcept
  {
         if constexpr(unsigned_scalar_value<T>)         return v;
    else if constexpr(floating_scalar_value<T>)         return bit_notand(Mzero(as(v)), v);
    else if constexpr(signed_integral_scalar_value<T>) 
    {
           if constexpr(sizeof(T) == 1)                 return _mm_abs_epi8(v);
      else if constexpr(sizeof(T) == 2)                 return _mm_abs_epi16(v);
      else if constexpr(sizeof(T) == 4)                 return _mm_abs_epi32(v);
      else if constexpr(sizeof(T) == 8)                 return abs_(EVE_RETARGET(cpu_), v);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<scalar_real_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> abs_(EVE_SUPPORTS(avx_)
                                       , wide<T, N, avx_> const &v) noexcept
  {
         if constexpr(unsigned_scalar_value<T>)  return v;
    else if constexpr(floating_scalar_value<T>)  return bit_notand(Mzero(as(v)), v);
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(sizeof(T) == 1)             return _mm256_abs_epi8(v);
        else if constexpr(sizeof(T) == 2)        return _mm256_abs_epi16(v);
        else if constexpr(sizeof(T) == 4)        return _mm256_abs_epi32(v);
        else if constexpr(sizeof(T) == 8)        return aggregate(eve::abs, v);
      }
      else                                       return aggregate(eve::abs, v);
    }
  }
}

#endif
