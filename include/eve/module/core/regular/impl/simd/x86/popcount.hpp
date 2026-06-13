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
      if constexpr (sizeof(T) == 1)
      {
        wide<T,fixed<16>> const lut = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4};
        wide<T,N> nibbles{15};
        wide<T,N> lo_count{_mm_shuffle_epi8(lut, x & nibbles)};
        wide<T,N> hi_count{_mm_shuffle_epi8(lut, _mm_and_si128(_mm_srli_epi16(x,4), nibbles))};
        return lo_count + hi_count;
      }
      else if constexpr (sizeof(T) == 2)
      {
        constexpr as<typename wide<T,N>::template rebind<std::uint8_t, eve::fixed<16>>> tgt = {};
        auto byte_counts = popcount(bit_cast(x,tgt));
        return wide<T,N>{_mm_maddubs_epi16(byte_counts, one(tgt))};
      }
      else if constexpr (sizeof(T) == 4)
      {
        constexpr as<typename wide<T,N>::template rebind<std::uint16_t, eve::fixed<8>>> tgt = {};
        auto byte_counts = popcount(bit_cast(x,tgt));
        return wide<T,N>{_mm_madd_epi16(byte_counts, one(tgt))};
      }
      else// if constexpr (sizeof(T) == 8)
      {
        constexpr as<typename wide<T,N>::template rebind<std::uint8_t, eve::fixed<16>>> tgt = {};
        auto byte_counts = popcount(bit_cast(x,tgt));
        return wide<T,N>{_mm_sad_epu8(byte_counts, _mm_setzero_si128())};
      }
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
      if constexpr (sizeof(T) == 1)
      {
        // Repeat LUT bit counts to fit 32bits
        wide<T,fixed<32>> const lut = { 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
                                      , 0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4
                                      };
        wide<T,N> nibbles{15};
        wide<T,N> lo_count{_mm256_shuffle_epi8(lut, x & nibbles)};
        wide<T,N> hi_count{_mm256_shuffle_epi8(lut, _mm256_and_si256(_mm256_srli_epi16(x,4), nibbles))};
        return lo_count + hi_count;
      }
      else if constexpr (sizeof(T) == 2)
      {
        constexpr as<typename wide<T,N>::template rebind<std::uint8_t, eve::fixed<32>>> tgt = {};
        auto byte_counts = popcount(bit_cast(x,tgt));
        return wide<T,N>{_mm256_maddubs_epi16(byte_counts, one(tgt))};
      }
      else if constexpr (sizeof(T) == 4)
      {
        constexpr as<typename wide<T,N>::template rebind<std::uint16_t, eve::fixed<16>>> tgt = {};
        auto byte_counts = popcount(bit_cast(x,tgt));
        return wide<T,N>{_mm256_madd_epi16(byte_counts, one(tgt))};
      }
      else// if constexpr (sizeof(T) == 8)
      {
        constexpr as<typename wide<T,N>::template rebind<std::uint8_t, eve::fixed<32>>> tgt = {};
        auto byte_counts = popcount(bit_cast(x,tgt));
        return wide<T,N>{_mm256_sad_epu8(byte_counts, _mm256_setzero_si256())};
      }
    }
    else
    {
      auto[l,h] = x.slice();
      return wide<T,N>(popcount[o](l),popcount[o](h));
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
