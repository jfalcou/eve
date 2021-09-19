//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE std::pair<int, bool>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(cpu_), logical<wide<T, fixed<4>>> mask)
    requires (current_api < avx512) && (sizeof(T) == 2)
  {
    static_assert(top_bits<logical<wide<T, fixed<4>>>>::bits_per_element == 2);
    auto to_bytes = eve::convert(mask, eve::as<eve::logical<std::uint8_t>>{});
    return compress_store_swizzle_mask_num(to_bytes);
  }

  template<typename T>
  EVE_FORCEINLINE std::pair<int, int>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(cpu_), logical<wide<T, fixed<8>>> mask)
    requires (current_api < avx512)
  {
    // aggregated
    if constexpr ( sizeof(T) == 8 )
    {
      auto to_u32 = eve::convert(mask, eve::as<logical<std::uint32_t>>{});
      return compress_store_swizzle_mask_num(to_u32);
    }
    else if constexpr ( sizeof(T) == 4 )
    {
      // Get 4 bits per integer
      // We want 1 + 1 + 3 + 3 + 9 + 9
      // We can almost achieve this with popcount
      // 0001 for 1
      // 0111 for 3
      // Can't do 9.
      // But we can mask and add
      //
      // sum from popcount:   [ 1, 1, 3, 3, 4, 1]
      // sum from extra mask: [ 0, 0, 0, 0, 5, 8]

      using u8_32 = typename wide<T, fixed<8>>::template rebind<std::uint8_t, eve::fixed<32>>;
      auto as_bytes = eve::bit_cast(mask, as<logical<u8_32>>{});

      std::uint32_t mmask = top_bits{as_bytes}.as_int();
      std::uint32_t idx_base_3 = std::popcount(mmask & 0x001f7711);
      std::uint32_t extra_mask = (mmask >> 17) & 0b1'101;

      idx_base_3 += extra_mask;

      return {(int)idx_base_3, std::popcount(mmask) / 4};
    }
    else if constexpr ( sizeof(T) == 2 )
    {
      // Alternative for shorts is to compute both halves
      // But that implies using _mm_extract_epi16 which has latency 3
      // as oppose to latency 1 for _mm_packs_epi16
      auto to_bytes = eve::convert(mask, eve::as<eve::logical<std::uint8_t>>{});
      return compress_store_swizzle_mask_num(to_bytes);
    }
    else if constexpr ( sizeof(T) == 1 )
    {
      // The problem is there is not really a good instruction to reduce 8 chars.
      // The closest we come is `_mm_sad_epu8`, it sums absolute differences for bytes.
      // We could use a zero mask.
      // But instead we can use the same mask we got to mask the 1, 3, 9.
      // The top is responisble for popcount.

      __m128i sad_mask = _mm_set_epi64x(0, 0x8080898983838181);
      __m128i sum      = _mm_sad_epu8(_mm_andnot_si128(mask, sad_mask), sad_mask);

      int desc     = _mm_cvtsi128_si32(sum);
      int num      = desc & 0x1f;
      int popcount = desc >> 7;
      return {num, popcount};
    }
  }
}
