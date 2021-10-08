//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE T sum_( EVE_SUPPORTS(sse2_), wide<T,N> v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    // We don't use AVX512 compound intrinsic _mm512_reduce_* as it generates worse code than us

    if constexpr( N::value == 1  )
    {
      return v.get(0);
    }
    // SSEx   ------------------------------------------------------------------------------------
    else if constexpr( c == category::float64x2  )
    {
      // Limit pressure on the shuffle port by using store port
      double tmp;
      _mm_storeh_pd(&tmp, v);
      return _mm_cvtsd_f64(v)+tmp;
    }
    else  if constexpr( c == category::float32x4  )
    {
      if constexpr( current_api >= sse3 )
      {
        // movehdup is faster than shuffle in SSE3
        __m128  bf   = _mm_movehdup_ps(v);
        __m128  sums = _mm_add_ps(v, bf);
        return _mm_cvtss_f32(_mm_add_ss(sums, _mm_movehl_ps(bf, sums)));
      }
      else
      {
        // Save a movaps and 2-3 uops by using movehl instead of second shuffle
        __m128  shuf  = _mm_shuffle_ps(v, v, _MM_SHUFFLE(2, 3, 0, 1));
        __m128  sums  = _mm_add_ps(v, shuf);
        return _mm_cvtss_f32(_mm_add_ss(sums, _mm_movehl_ps(shuf, sums)));
      }
    }
    else  if constexpr( c == category::int32x4 || c == category::uint32x4 )
    {
      constexpr auto shuf =  _MM_SHUFFLE(1, 0, 3, 2);
      __m128i sum64 = _mm_add_epi32(v    , _mm_shuffle_epi32  (v    , shuf));
      __m128i sum32 = _mm_add_epi32(sum64, _mm_shufflelo_epi16(sum64, shuf));
      return _mm_cvtsi128_si32(sum32);
    }
    else  if constexpr( c == category::int16x8 || c == category::uint16x8 )
    {
      // no int16 shuffle, so we optimize using other ways
      __m128i r = _mm_set1_epi32(0);
              r = _mm_add_epi32(r, _mm_madd_epi16(v, _mm_set1_epi16(1)));
              r = _mm_add_epi32(r, _mm_srli_si128(r, 8));
              r = _mm_add_epi32(r, _mm_srli_si128(r, 4));

      return T(_mm_cvtsi128_si32(r));
    }
    else  if constexpr( c == category::int8x16 || c == category::uint8x16 )
    {
      // no int8 shuffle, so we optimize using other ways
      __m128i o = _mm_set1_epi16(1);
      __m128i z = _mm_set1_epi8(0);

      __m128i r = _mm_set1_epi32(0);
              r = _mm_add_epi32(r, _mm_madd_epi16(_mm_unpacklo_epi8(v, z), o));
              r = _mm_add_epi32(r, _mm_madd_epi16(_mm_unpackhi_epi8(v, z), o));
              r = _mm_add_epi32(r, _mm_srli_si128(r, 8));
              r = _mm_add_epi32(r, _mm_srli_si128(r, 4));

      return T(_mm_cvtsi128_si32(r));
    }
    // AVX2 -----------------------------------------------------------------------------------
    else if constexpr( current_api >= avx2 )
    {
      if constexpr( c == category::int32x8 || c == category::uint32x8  )
      {
        wide<T,N> s = _mm256_add_epi32(v, _mm256_srli_si256(v , 8));
                  s = _mm256_add_epi32(s, _mm256_srli_si256(s , 4));
        return    s.get(0) + s.get(1);
      }
      else  if constexpr( c == category::int16x16|| c == category::uint16x16 )
      {
        wide<T,N> s = _mm256_hadd_epi16(v, v);
                  s = _mm256_hadd_epi16(s, s);
                  s = _mm256_hadd_epi16(s, s);
        return    s.get(0) + s.get(15);
      }
      else  if constexpr( c == category::int8x32 || c == category::uint8x32  )
      {
        __m256i z = _mm256_set1_epi8(0);
        wide<upgrade_t<T>,typename N::split_type> s = _mm256_add_epi16( _mm256_unpacklo_epi8(v, z)
                                                                      , _mm256_unpackhi_epi8(v, z)
                                                                      );
        return static_cast<T>(sum(s));
      }
      else
      {
        auto[l,h] = v.slice();
        return sum(l+h);
      }
    }
    // else other types use common cases
    else
    {
      return sum_(EVE_RETARGET(cpu_), v);
    }
  }
}
