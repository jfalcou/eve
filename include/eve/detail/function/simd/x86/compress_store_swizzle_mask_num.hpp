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
  template<eve::relative_conditional_expr C, typename T>
  EVE_FORCEINLINE std::pair<int, bool>
  compress_store_swizzle_mask_num_partial_(EVE_SUPPORTS(sse2_), C c, logical<wide<T, fixed<4>>> mask)
    requires (current_api < avx512) && (sizeof(T) == 2)
  {
    static_assert(top_bits<logical<wide<T, fixed<4>>>>::bits_per_element == 2);
    auto to_bytes = eve::convert(mask, eve::as<eve::logical<std::uint8_t>>{});
    return compress_store_swizzle_mask_num_partial(c, to_bytes);
  }

  template<eve::relative_conditional_expr C, typename T>
  EVE_FORCEINLINE std::pair<int, int>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(sse2_), C c, logical<wide<T, fixed<4>>> mask)
    requires (current_api < avx512) && (sizeof(T) <= 4)
  {
    if constexpr (sizeof(T) == 4 && eve::current_api >= sse4_1)
    {
      return compress_store_swizzle_mask_num_(EVE_RETARGET(cpu_), c, mask);
    }
    else if constexpr (sizeof(T) == 4)
    {
      // Alternativatly we can add shorts in scalar but this a very cheap conversion
      return compress_store_swizzle_mask_num(c, convert(mask, eve::as<logical<std::uint16_t>>{}));
    }
    else
    {
      using bits_type = typename logical<wide<T, fixed<4>>>::bits_type;
      mask = mask && c.mask(eve::as(mask));

      bits_type sad_mask {0x81, 0x82, 0x84, 0x80};
      bits_type sum = _mm_sad_epu8(_mm_andnot_si128(mask, sad_mask), sad_mask);
      int desc      = _mm_cvtsi128_si32(sum);

      int num      = desc & 0xf;
      int popcount = desc >> 7;

      return {num, popcount};
    }
  }

  template<typename T>
  EVE_FORCEINLINE std::pair<int, int>
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(sse2_), logical<wide<T, fixed<8>>> mask)
    requires (current_api < avx512)
  {
    // aggregated
    if constexpr ( eve::has_aggregated_abi_v<wide<T, fixed<8>>> )
    {
      using half_t = make_integer_t<sizeof(T) / 2, unsigned>;
      auto half = eve::convert(mask, eve::as<logical<half_t>>{});
      return compress_store_swizzle_mask_num(half);
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

  template<typename T>
  EVE_FORCEINLINE auto
  compress_store_swizzle_mask_num_(EVE_SUPPORTS(sse2_), logical<wide<T, fixed<16>>> mask)
    requires (current_api < avx512) && x86_abi<abi_t<T, fixed<16>>> // For aggregated 16 elements
                                                                    // just do the base case.
  {
    if constexpr ( sizeof(T) == 2 )
    {
      auto to_bytes = eve::convert(mask, eve::as<eve::logical<std::uint8_t>>{});
      return compress_store_swizzle_mask_num(to_bytes);
    }
    else if constexpr ( sizeof(T) == 1 )
    {
      __m128i sad_mask = _mm_set_epi64x(0x8080898983838181, 0x8080898983838181);
      __m128i sum      = _mm_sad_epu8(_mm_andnot_si128(mask, sad_mask), sad_mask);

      int desc_lo = _mm_cvtsi128_si32(sum);
      int desc_hi = _mm_extract_epi16(sum, 4);

      struct res {
        int l_num;
        int l_count;
        int h_num;
        int h_count;
      };

      return res {
        desc_lo  & 0x1f,
        desc_lo >> 7,
        desc_hi & 0x1f,
        desc_hi >> 7
      };
    }
  }

}
