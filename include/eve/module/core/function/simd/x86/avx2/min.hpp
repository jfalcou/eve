//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2019 Joel FALCOU
   Copyright 2019 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_MIN_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_AVX2_MIN_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_less.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_> min_(EVE_SUPPORTS(avx2_)
                                       , wide<T, N, avx_> const &v0
                                       , wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, double>) return  _mm256_min_pd(v1,v0);
      if constexpr(std::is_same_v<T, float>)  return  _mm256_min_ps(v1,v0);
    }
    else
    {
      if  constexpr(std::is_signed_v<T>)
      {
        if  constexpr(sizeof(T) == 1) return _mm256_min_epi8(v0, v1);
        if  constexpr(sizeof(T) == 2) return _mm256_min_epi16(v0, v1);
        if  constexpr(sizeof(T) == 4) return _mm256_min_epi32(v0, v1);
        if  constexpr(sizeof(T) == 8) return if_else(is_less(v1, v0), v1, v0);
      }
      else
      {
        if constexpr(sizeof(T) == 1) return _mm256_min_epu8(v0, v1);
        if constexpr(sizeof(T) == 2) return _mm256_min_epu16(v0, v1);
        if constexpr(sizeof(T) == 4) return _mm256_min_epu32(v0, v1);   
        if constexpr(sizeof(T) == 8) return if_else(is_less(v1, v0), v1, v0);
      }
    }
  } 
}

#endif
