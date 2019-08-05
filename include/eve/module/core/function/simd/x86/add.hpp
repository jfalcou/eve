//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_ADD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_ADD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
  add_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    if constexpr( std::is_same_v<T,double>  ) return _mm_add_pd(v0, v1);
    if constexpr( std::is_same_v<T,float>   ) return _mm_add_ps(v0, v1);
    if constexpr( std::is_integral_v<T>     )
    {
      if constexpr(sizeof(T) == 1)  return _mm_add_epi8(v0, v1);
      if constexpr(sizeof(T) == 2)  return _mm_add_epi16(v0, v1);
      if constexpr(sizeof(T) == 4)  return _mm_add_epi32(v0, v1);
      if constexpr(sizeof(T) == 8)  return _mm_add_epi64(v0, v1);
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
  add_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v0, wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_same_v<T, float>)  return _mm256_add_ps(v0, v1);
    if constexpr(std::is_same_v<T, double>) return _mm256_add_pd(v0, v1);

    if constexpr(current_api == avx2)
    {
      if constexpr(std::is_integral_v<T> && sizeof(T) == 1) return _mm256_add_epi8(v0, v1);
      if constexpr(std::is_integral_v<T> && sizeof(T) == 2) return _mm256_add_epi16(v0, v1);
      if constexpr(std::is_integral_v<T> && sizeof(T) == 4) return _mm256_add_epi32(v0, v1);
      if constexpr(std::is_integral_v<T> && sizeof(T) == 8) return _mm256_add_epi64(v0, v1);
    }
    else
    {
      if constexpr(std::is_integral_v<T>)     return aggregate(eve::add, v0, v1);
    }
  }
}

#endif
