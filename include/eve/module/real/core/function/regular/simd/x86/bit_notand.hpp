//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>
#include <eve/concept/value.hpp>

namespace eve ::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_notand_(EVE_SUPPORTS(sse2_), wide<T, N> const &v0, wide<T, N> const &v1) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if constexpr(std::is_same_v<T, float>)       return _mm_andnot_ps(v0, v1);
    else if constexpr(std::is_same_v<T, double>) return _mm_andnot_pd(v0, v1);
    else if constexpr(std::is_integral_v<T>)     return _mm_andnot_si128(v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_notand_(EVE_SUPPORTS(avx_), wide<T, N> const &v0, wide<T, N> const &v1) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if constexpr(std::is_same_v<T, float>)       return _mm256_andnot_ps(v0, v1);
    else if constexpr(std::is_same_v<T, double>) return _mm256_andnot_pd(v0, v1);
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(current_api >= avx2)           return _mm256_andnot_si256(v0, v1);
      else return _mm256_castps_si256(_mm256_andnot_ps(_mm256_castsi256_ps(v0), _mm256_castsi256_ps(v1)));
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 512 bits implementation
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE wide<T, N> bit_notand_(EVE_SUPPORTS(avx512_), wide<T, N> const &v0, wide<T, N> const &v1) noexcept
    requires std::same_as<abi_t<T, N>, x86_512_>
  {
         if constexpr ( std::is_same_v<T, double> ) return _mm512_andnot_pd(v0, v1);
    else if constexpr ( std::is_same_v<T, float>  ) return _mm512_andnot_ps(v0, v1);
    else if constexpr ( sizeof(T) == 8            ) return _mm512_andnot_epi64(v0, v1);
    else if constexpr ( sizeof(T) == 4            ) return _mm512_andnot_epi32(v0, v1);
    else                                            return _mm512_andnot_si512(v0, v1);
  }
}
