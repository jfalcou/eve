//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_MAX_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_MAX_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_> max_(EVE_SUPPORTS(sse2_)
                                       , wide<T, N, sse_> const &v0
                                       , wide<T, N, sse_> const &v1) noexcept
  {
         if constexpr(std::is_same_v<T, double>)     return _mm_max_pd(v0, v1);
    else if constexpr(std::is_same_v<T, float>)      return _mm_max_ps(v0, v1);
    else if constexpr( std::is_integral_v<T>)
    {
      constexpr bool issigned = std::is_signed_v<T>;
      if constexpr(issigned && sizeof(T) == 2)       return _mm_max_epi16(v0, v1);
      else if constexpr(!issigned && sizeof(T) == 1) return _mm_max_epu8(v0, v1);
      else if constexpr(current_api >= sse4_1 && (sizeof(T) != 8))
      {
        if constexpr(issigned)
        {
          if constexpr(sizeof(T) == 1)               return _mm_max_epi8(v0, v1);
          else if constexpr(sizeof(T) == 4)          return _mm_max_epi32(v0, v1);
        }
        else
        {
          if constexpr(sizeof(T) == 2)               return _mm_max_epu16(v0, v1);
          else if constexpr(sizeof(T) == 4)          return _mm_max_epu32(v0, v1);
        }
      }
      else                                           return map(max, v0, v1);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> max_(EVE_SUPPORTS(avx_)
                                       , wide<T, N, avx_> const &v0
                                       , wide<T, N, avx_> const &v1) noexcept
  {
         if constexpr(std::is_same_v<T, float>)        return _mm256_max_ps(v0, v1);
    else if constexpr(std::is_same_v<T, double>)       return _mm256_max_pd(v0, v1);
    else // if constexpr(std::is_integral_v<T>)
    {
      if constexpr(current_api >= avx2 && sizeof(T) != 8)
      {
        if constexpr(std::is_signed_v<T>)
        {
          if constexpr(sizeof(T) == 1)                 return _mm256_max_epi8(v0, v1);
          else if constexpr(sizeof(T) == 2)            return _mm256_max_epi16(v0, v1);
          else if constexpr(sizeof(T) == 4)            return _mm256_max_epi32(v0, v1);
        }
        else
        {
          if constexpr(sizeof(T) == 1)                 return _mm256_max_epu8(v0, v1);
          else if constexpr(sizeof(T) == 2)            return _mm256_max_epu16(v0, v1);
          else if constexpr(sizeof(T) == 4)            return _mm256_max_epu32(v0, v1);
        }
      }
      else                                             return aggregate(max, v0, v1);
    }
  }
}

#endif
