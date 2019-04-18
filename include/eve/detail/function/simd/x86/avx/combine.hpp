//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_X86_AVX_COMBINE_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_X86_AVX_COMBINE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // All AVX types
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(avx_ const &, wide<T, N, avx_> const &l, wide<T, N, avx_> const &h) noexcept
  {
    using that_t = typename wide<T, typename N::combined_type>::storage_type;
    return that_t{l, h};
  }

  // -----------------------------------------------------------------------------------------------
  // All SSE types
  template<typename T, typename N>
  EVE_FORCEINLINE auto
  combine(avx_ const &, wide<T, N, sse_> const &l, wide<T, N, sse_> const &h) noexcept
  {
    if constexpr(N::value * sizeof(T) == limits<eve::sse2_>::bytes)
    {
      if constexpr(std::is_same_v<T, double>)
        return _mm256_insertf128_pd(_mm256_castpd128_pd256(l), h, 1);

      if constexpr(std::is_same_v<T, float>)
        return _mm256_insertf128_ps(_mm256_castps128_ps256(l), h, 1);

      if constexpr(std::is_integral_v<T>)
        return _mm256_insertf128_si256(_mm256_castsi128_si256(l), h, 1);
    }
    else
    {
      return combine(sse2_{}, l, h);
    }
  }
}

#endif
