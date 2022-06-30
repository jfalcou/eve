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
#include <eve/detail/remove_garbage.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE T sum_( EVE_SUPPORTS(sse2_), wide<T,N> v) noexcept
  requires x86_abi<abi_t<T, N>>
  {
    constexpr auto c = categorize<wide<T, N>>();

    // We don't use AVX512 compound intrinsic _mm512_reduce_* as it generates worse code than us
    // https://stackoverflow.com/questions/60108658/fastest-method-to-calculate-sum-of-all-packed-32-bit-integers-using-avx512-or-av

    if constexpr( N::value == 1  )
    {
      return v.get(0);
    }
    // SSEx   ------------------------------------------------------------------------------------
    // Most of those implementations derives from:
    // https://stackoverflow.com/questions/6996764/fastest-way-to-do-horizontal-sse-vector-sum-or-other-reduction
    else if constexpr( c == category::float64x2  )
    {
      // Limit pressure on the shuffle port by using store port
      double tmp;
      _mm_storeh_pd(&tmp, v);
      return _mm_cvtsd_f64(v)+tmp;
    }
    else  if constexpr( c == category::float32x4  )
    {
      // Clean up garbage if needed
      v = slide_garbage(v);

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
      // Clean up garbage if needed
      v = slide_garbage(v);

      constexpr auto shuf =  _MM_SHUFFLE(1, 0, 3, 2);
      __m128i sum64;

      if constexpr(current_api >= avx)  sum64 = _mm_add_epi32(v, _mm_unpackhi_epi64(v,v));
      else                              sum64 = _mm_add_epi32(v, _mm_shuffle_epi32(v,shuf));

      __m128i sum32 = _mm_add_epi32(sum64, _mm_shufflelo_epi16(sum64, shuf));
      return _mm_cvtsi128_si32(sum32);
    }
    else  if constexpr( c == category::uint8x16 || c == category::int8x16 )
    {
      // Clean up garbage if needed
      v = slide_garbage(v);

      // https://stackoverflow.com/questions/36998538/fastest-way-to-horizontally-sum-sse-unsigned-byte-vector
      __m128i vsum = _mm_sad_epu8(v, _mm_setzero_si128());
      auto r = _mm_cvtsi128_si32(vsum);

      r += _mm_extract_epi16(vsum, 4);
      return r;
    }
    // AVX/AVX2 -----------------------------------------------------------------------------------
    else if constexpr( current_api >= avx )
    {
      // Always better or similar than other approach
      auto[l,h] = v.slice();
      return sum(l+h);
    }
    // else other types use common cases
    else
    {
      return sum_(EVE_RETARGET(cpu_), v);
    }
  }
}
