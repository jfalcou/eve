//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_X86_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_X86_MUL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <eve/constant/constant.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // 128 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, sse_>
                  mul_(EVE_SUPPORTS(sse2_), wide<T, N, sse_> const &v0, wide<T, N, sse_> const &v1) noexcept
  {
    if constexpr(std::is_same_v<T, double>)
      return _mm_mul_pd(v0, v1);
    else if constexpr(std::is_same_v<T, float>)
      return _mm_mul_ps(v0, v1);
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(sizeof(T) == 1)
      {
        auto mask = Constant<wide<std::int16_t, fixed<N::value / 2>>, 0x00FF>();
        return _mm_or_si128(
            _mm_and_si128(mask, _mm_mullo_epi16(v0, v1)),
            _mm_slli_epi16(
                _mm_and_si128(mask, _mm_mullo_epi16(_mm_srli_epi16(v0, 8), _mm_srli_epi16(v1, 8))),
                8));
      }
      else if constexpr(sizeof(T) == 2)
        return _mm_mullo_epi16(v0, v1);
      else if constexpr(sizeof(T) == 4)
      {
        if constexpr(current_api >= sse4_1)
          return _mm_mullo_epi32(v0, v1);
        else
        {
#ifdef __clang__
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wshadow"
#endif
          auto mask = _mm_setr_epi32(0xffffffff, 0, 0xffffffff, 0);
          return _mm_or_si128(
              _mm_and_si128(_mm_mul_epu32(v0, v1), mask),
              _mm_slli_si128(
                  _mm_and_si128(_mm_mul_epu32(_mm_srli_si128(v0, 4), _mm_srli_si128(v1, 4)), mask),
                  4));
#ifdef __clang__
#  pragma clang diagnostic pop
#endif
        }
      }
      else
      {
        return map(mul, v0, v1);
      }
    }
  }

  // -----------------------------------------------------------------------------------------------
  // 256 bits implementation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, avx_>
                  mul_(EVE_SUPPORTS(avx_), wide<T, N, avx_> const &v0, wide<T, N, avx_> const &v1) noexcept
  {
    if constexpr(std::is_same_v<T, float>)
      return _mm256_mul_ps(v0, v1);
    else if constexpr(std::is_same_v<T, double>)
      return _mm256_mul_pd(v0, v1);
    else if constexpr(std::is_integral_v<T>)
    {
      if constexpr(current_api >= avx2)
      {
        if constexpr(sizeof(T) == 1)
        {
          auto       mask = Constant<wide<std::int16_t, fixed<N::value / 2>>, 0x00FF>();
          auto const hmul = _mm256_mullo_epi16(_mm256_srli_epi16(v0.storage(), 8),
                                               _mm256_srli_epi16(v1.storage(), 8));

          return _mm256_or_si256(_mm256_and_si256(mask, _mm256_mullo_epi16(v0, v1)),
                                 _mm256_slli_epi16(_mm256_and_si256(mask, hmul), 8));
        }
        else if constexpr(sizeof(T) == 2)
          return _mm256_mullo_epi16(v0, v1);
        else if constexpr(sizeof(T) == 4)
          return _mm256_mullo_epi32(v0, v1);
        else
          return map(mul, v0, v1);
      }
      else
      {
        return aggregate(eve::mul, v0, v1);
      }
    }
  }
}

#endif
