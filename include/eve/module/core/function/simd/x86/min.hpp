//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>
#include <eve/function/if_else.hpp>
#include <type_traits>

namespace eve::detail
{
  template <eve::simd_value Wide>
  EVE_FORCEINLINE Wide if_else_min(Wide x, Wide y)
  {
    return eve::if_else(x > y, y, x);
  }

  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_128_> min_(EVE_SUPPORTS(sse2_)
                                       , wide<T, N, x86_128_> const &v0
                                       , wide<T, N, x86_128_> const &v1) noexcept
  {
         if constexpr(std::is_same_v<T, double>) return _mm_min_pd(v0, v1);
    else if constexpr(std::is_same_v<T, float>)  return _mm_min_ps(v0, v1);
    else if constexpr(sizeof(T) == 1)
    {
           if constexpr(!std::is_signed_v<T>)    return _mm_min_epu8(v0, v1);
      else if constexpr(current_api >= sse4_1)   return _mm_min_epi8(v0, v1);
      else                                       return detail::if_else_min(v0, v1);
    }
    else if constexpr(sizeof(T) == 2)
    {
           if constexpr(std::is_signed_v<T>)    return _mm_min_epi16(v0, v1);
      else if constexpr(current_api >= sse4_1)  return _mm_min_epu16(v0, v1);
      else                                      return detail::if_else_min(v0, v1);
    }
    else if constexpr(sizeof(T) == 4)
    {
           if constexpr(current_api < sse4_1)   return detail::if_else_min(v0, v1);
      else if constexpr(std::is_signed_v<T>)    return _mm_min_epi32(v0, v1);
      else                                      return _mm_min_epu32(v0, v1);
    }
    else
    {
           if constexpr(current_api >= sse4_2)  return detail::if_else_min(v0, v1);
      else                                      return map(min, v0, v1);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N, x86_256_> min_(EVE_SUPPORTS(avx_)
                                       , wide<T, N, x86_256_> const &v0
                                       , wide<T, N, x86_256_> const &v1) noexcept
  {
         if constexpr(std::is_same_v<T, float>)            return _mm256_min_ps(v0, v1);
    else if constexpr(std::is_same_v<T, double>)           return _mm256_min_pd(v0, v1);
    else if constexpr(current_api == avx && sizeof(T) < 8) return aggregate(min, v0, v1);
    else if constexpr(sizeof(T) == 8)                      return detail::if_else_min(v0, v1);
    else if constexpr(std::is_signed_v<T>)
      {
             if constexpr(sizeof(T) == 1)                  return _mm256_min_epi8(v0, v1);
        else if constexpr(sizeof(T) == 2)                  return _mm256_min_epi16(v0, v1);
        else if constexpr(sizeof(T) == 4)                  return _mm256_min_epi32(v0, v1);
      }
    else
      {
             if constexpr(sizeof(T) == 1)                  return _mm256_min_epu8(v0, v1);
        else if constexpr(sizeof(T) == 2)                  return _mm256_min_epu16(v0, v1);
        else if constexpr(sizeof(T) == 4)                  return _mm256_min_epu32(v0, v1);
      }
  }
}
