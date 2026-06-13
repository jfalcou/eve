//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve::_
{
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto popcount_(EVE_REQUIRES(sse2_), O const& o, wide<T, N> x) noexcept
  requires std::same_as<abi_t<T, N>, x86_128_>
  {
    if      constexpr (sizeof(T) == 1 && supports_avx512vl && supports_avx512bitalg_  ) return _mm_popcnt_epi8(x);
    else if constexpr (sizeof(T) == 2 && supports_avx512vl && supports_avx512bitalg_  ) return _mm_popcnt_epi16(x);
    else if constexpr (sizeof(T) == 4 && supports_avx512vl && supports_avx512popcntdq_) return _mm_popcnt_epi32(x);
    else if constexpr (sizeof(T) == 8 && supports_avx512vl && supports_avx512popcntdq_) return _mm_popcnt_epi64(x);
    else if constexpr (current_api >= eve::ssse3)
    {
      __m128i lut  = _mm_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
      __m128i mask = _mm_set1_epi8(0x0F);

      __m128i lo_count = _mm_shuffle_epi8(lut, _mm_and_si128(x, mask));
      __m128i hi_count = _mm_shuffle_epi8(lut, _mm_and_si128(_mm_srli_epi16(x, 4), mask));
      __m128i count8   = _mm_add_epi8(lo_count, hi_count);

      if constexpr (sizeof(T) == 1) return wide<T,N>{count8};
      if constexpr (sizeof(T) == 8) return wide<T,N>{_mm_sad_epu8(count8, _mm_setzero_si128())};

      __m128i count16 = _mm_maddubs_epi16(count8, _mm_set1_epi8(1));

      if constexpr (sizeof(T) == 2) return wide<T,N>{count16};
      if constexpr (sizeof(T) == 4) return wide<T,N>{_mm_madd_epi16(count16, _mm_set1_epi16(1))};
    }
    else
    {
      return popcount.behavior(cpu_{}, o, x);
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // 256 bits
template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto popcount_(EVE_REQUIRES(avx_), O const& o, wide<T, N> x) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_>
  {
    if      constexpr (sizeof(T) == 1 && supports_avx512vl && supports_avx512bitalg_  ) return _mm256_popcnt_epi8(x);
    else if constexpr (sizeof(T) == 2 && supports_avx512vl && supports_avx512bitalg_  ) return _mm256_popcnt_epi16(x);
    else if constexpr (sizeof(T) == 4 && supports_avx512vl && supports_avx512popcntdq_) return _mm256_popcnt_epi32(x);
    else if constexpr (sizeof(T) == 8 && supports_avx512vl && supports_avx512popcntdq_) return _mm256_popcnt_epi64(x);
    else if constexpr (current_api >= eve::avx2)
    {
      // We broadcast the 128bits LUT as it generates better codegen than using _mm256_setr_epi8
      __m128i lut_128 = _mm_setr_epi8(0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4);
      __m256i lut     = _mm256_broadcastsi128_si256(lut_128);
      __m256i mask    = _mm256_set1_epi8(0x0F);

      __m256i lo_count = _mm256_shuffle_epi8(lut, _mm256_and_si256(x, mask));
      __m256i hi_count = _mm256_shuffle_epi8(lut, _mm256_and_si256(_mm256_srli_epi16(x, 4), mask));
      __m256i count8   = _mm256_add_epi8(lo_count, hi_count);

      if constexpr (sizeof(T) == 1) return wide<T,N>{count8};
      if constexpr (sizeof(T) == 8) return wide<T,N>{_mm256_sad_epu8(count8, _mm256_setzero_si256())};

      __m256i count16 = _mm256_maddubs_epi16(count8, _mm256_set1_epi8(1));

      if constexpr (sizeof(T) == 2) return wide<T,N>{count16};
      if constexpr (sizeof(T) == 4) return wide<T,N>{_mm256_madd_epi16(count16, _mm256_set1_epi16(1))};
    }
    else
    {
      auto[l,h] = x.slice();
      return wide<T,N>(popcount[o](l), popcount[o](h));
    }
  }

  /////////////////////////////////////////////////////////////////////////////
  // 512 bits
  template<unsigned_scalar_value T, typename N, callable_options O>
  EVE_FORCEINLINE auto popcount_(EVE_REQUIRES(avx_), O const& o, wide<T, N> x) noexcept
    requires std::same_as<abi_t<T, N>, x86_512_>
  {
    if      constexpr (sizeof(T) == 1 && supports_avx512vl && supports_avx512bitalg_  ) return _mm512_popcnt_epi8(x);
    else if constexpr (sizeof(T) == 2 && supports_avx512vl && supports_avx512bitalg_  ) return _mm512_popcnt_epi16(x);
    else if constexpr (sizeof(T) == 4 && supports_avx512vl && supports_avx512popcntdq_) return _mm512_popcnt_epi32(x);
    else if constexpr (sizeof(T) == 8 && supports_avx512vl && supports_avx512popcntdq_) return _mm512_popcnt_epi64(x);
    else
    {
      auto[l,h] = x.slice();
      return wide<T,N>(popcount[o](l),popcount[o](h));
    }
  }
}
