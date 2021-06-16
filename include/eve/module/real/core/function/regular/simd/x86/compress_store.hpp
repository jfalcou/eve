//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <array>
#include <bit>

namespace eve::detail
{

  EVE_FORCEINLINE constexpr std::uint32_t add_popcount(std::uint32_t idx, std::uint32_t count)
  {
    return count << 4 | idx;
  }

  EVE_FORCEINLINE constexpr std::uint8_t get_popcount(std::uint8_t idx) {
    return idx >> 4;
  }

  template <std::unsigned_integral T>
  EVE_FORCEINLINE constexpr auto pattern_4_elements(std::array<T, 8> idxs)
  {
    using row = std::array<T, 4>;

    return std::array {
      row{ idxs[3],       0,       0,       0 },  // 000
      row{ idxs[0], idxs[3],       0,       0 },  // 001
      row{ idxs[1], idxs[3],       0,       0 },  // 010
      row{ idxs[0], idxs[1], idxs[3],       0 },  // 011
      row{ idxs[2], idxs[3],       0,       0 },  // 100
      row{ idxs[0], idxs[2], idxs[3],       0 },  // 101
      row{ idxs[1], idxs[2], idxs[3],       0 },  // 110
      row{ idxs[0], idxs[1], idxs[2], idxs[3] },  // 111
    };
  }

  template <std::unsigned_integral T>
  constexpr auto idxs_bytes = [] {
    std::array<T, 8> res = {};

    for (unsigned i = 0; i != 8; ++i)
    {
      unsigned byte_idx = i * sizeof(T);

      if constexpr ( sizeof(T) == 4 )
      {
        res[i] = (byte_idx + 3) << 24 | (byte_idx + 2) << 16 | (byte_idx + 1) << 8 | byte_idx;
      }
      else if constexpr ( sizeof(T) == 2 )
      {
        res[i] = (byte_idx + 1) << 8 | byte_idx;
      }
      else if constexpr ( sizeof(T) == 1 )
      {
        res[i] = byte_idx;
      }
    }

    return res;
  }();

  template <std::unsigned_integral T>
  constexpr auto idx_dwords = [] {
    std::array<T, 8> res = {};

    for (unsigned i = 0; i != 8; i += 1)
    {
      unsigned dword_idx = i * sizeof(T) / 4;

      if constexpr ( sizeof(T) == 8 )
      {
        res[i] = std::uint64_t(dword_idx + 1) << 32 | dword_idx;
      }
      else if constexpr ( sizeof(T) == 4 )
      {
        res[i] = dword_idx;
      }
    }

    return res;
  }();

  template <typename Row, std::size_t N>
  EVE_FORCEINLINE constexpr auto add_popcounts(std::array<Row, N> patterns)
  {
    for (std::uint8_t i = 0; i != patterns.size(); ++i) {
      patterns[i][0] = add_popcount(patterns[i][0], std::popcount(i));
    }
    return patterns;
  }

  template <typename T, typename N>
  EVE_FORCEINLINE wide<T, N> permvar8(wide<T, N> v, __m256i pattern)
    requires (current_api >= avx2)
  {
         if constexpr ( std::integral<T>       ) return _mm256_permutevar8x32_epi32(v, pattern);
    else if constexpr ( std::same_as<T, float> ) return _mm256_permutevar8x32_ps   (v, pattern);
    else
    {
      __m256 f32s = _mm256_castpd_ps(v);
      f32s = _mm256_permutevar8x32_ps(f32s, pattern);
      return _mm256_castps_pd(f32s);
    }
  }

  // The idea from: https://gist.github.com/aqrit/6e73ca6ff52f72a2b121d584745f89f3#file-despace-cpp-L141
  // Was shown to me by: @aqrit
  // Stack Overflow discussion: https://chat.stackoverflow.com/rooms/212510/discussion-between-denis-yaroshevskiy-and-peter-cordes
  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(ssse3_),
                     unsafe_type,
                     wide<T, N> v,
                     logical<wide<T, N>> mask,
                     Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
    if constexpr ( N() == 4 && sizeof(T) == 8 && current_api == avx  )
    {
      return compress_store_aggregated_unsafe(v, mask, ptr);
    }
    else if constexpr ( N() == 4 && sizeof(T) == 8 )
    {
      alignas(sizeof(T) * N()) auto patterns = pattern_4_elements(idx_dwords<std::uint64_t>);

      top_bits mmask{mask};
      aligned_ptr<std::uint64_t, eve::fixed<4>> pattern_ptr{patterns[mmask.as_int() & 7].data()};
      wide<std::uint32_t, eve::fixed<8>> pattern{ptr_cast<std::uint32_t>(pattern_ptr)};

      wide<T, N> shuffled = permvar8(v, pattern);

      store(shuffled, ptr);
      int popcount = eve::count_true(mask);
      return as_raw_pointer(ptr) + popcount;
    }
    else if constexpr ( std::floating_point<T> )
    {
      using i_t = eve::as_integer_t<T>;
      auto  i_p = ptr_cast<i_t>(ptr);
      auto  i_v = eve::bit_cast(v, eve::as_<wide<i_t, N>>{});
      auto  i_m = eve::bit_cast(mask, eve::as_<eve::logical<wide<i_t, N>>>{});

      i_t* stored = unsafe(compress_store)(i_v, i_m, i_p);
      return (T*) stored;
    }
    else
    {
      using u_t         = eve::as_integer_t<T, unsigned>;
      using bytes_fixed = eve::fixed<N() * sizeof(T)>;
      using bytes_t = typename wide<T, N>::template rebind<std::uint8_t, bytes_fixed>;

      alignas(sizeof(T) * 4) const auto patterns = add_popcounts(pattern_4_elements(idxs_bytes<u_t>));

      auto mmask = [&] {
        if constexpr ( sizeof(T) == 2 && abi_t<T, N>::is_wide_logical )
        {
          return _mm_movemask_epi8(_mm_packs_epi16(mask, mask));
        }
        else
        {
          return top_bits{mask}.as_int();
        }
      }();

      using a_p = aligned_ptr<u_t const, N>;
      bytes_t pattern(ptr_cast<std::uint8_t const>( a_p(patterns[mmask & 7].data()) ));

      wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);
      store(shuffled, ptr);

      int popcount = get_popcount(pattern.get(0)) + (bool)(mmask & 8);
      return as_raw_pointer(ptr) + popcount;
    }
  }

  /*
    Credit again goes to @aqrit.

    See comment in compress store for 8 elements first.
    00 should become 0, 10|01 -> 1, 11 -> 2.
    This is adding digigts.

    We have 3 pairs, so the first 1 should correspond to power 0, second to 1, third 3 - 2

    So we should & with [1, 1, 3, 3, 9, 9] and then reduce.

    Now, the problem is there is not really a good instruction to reduce 8 numbers.
    The closest we come is `_mm_sad_epu8`.
    However, it sums absolute differences for bytes.
    We could use a zero mask.
    But instead we can use the same mask we got to mask the 1, 3, 9.
    In order to get the result in the correct order, we need to use `andnot` instead of `and`.
    For 8 integers we can use a popcount + some math.

    Example:
    (true, false, true, true, true, false, false, false)
     1             3    3      9
     reduced is 16

    NOTE: we could also use mmx intrinsics but tend to not use them.
  */
  template <real_scalar_value T, typename N>
  EVE_FORCEINLINE
  std::pair<std::uint32_t, std::uint16_t>
  base_3_mask(eve::logical<eve::wide<T, N>> m) {
    if constexpr ( sizeof(T) == 4 && N() == 8 && current_api == avx2 )
    {
      std::uint32_t mmask = _mm256_movemask_epi8(
         eve::bit_cast(m, eve::as_<logical<eve::wide<std::uint32_t, N>>>{})
      );

      // sum from popcount:   [ 1, 1, 3, 3, 4, 1]
      // sum from extra mask: [ 0, 0, 0, 0, 5, 8]
      std::uint32_t idx_base_3 = std::popcount(mmask & 0x001f7711);
      std::uint32_t extra_mask = (mmask >> 17) & 0b1'101;
      idx_base_3 += extra_mask;

      return {idx_base_3, std::popcount(mmask) / 4};
    }
    else if constexpr ( sizeof(T) <= 2 && N() == 8 )
    {
      // Alternative for shorts is to compute both halves
      // But that implies using _mm_extract_epi16 which has latency 3
      // as oppose to latency 1 for _mm_packs_epi16
      __m128i raw = [&] () -> __m128i {
        if constexpr ( sizeof(T) == 2 ) return _mm_packs_epi16(m, m);
        else                            return m;
      }();

      __m128i sad_mask = _mm_set_epi64x(0, 0x8080898983838181);
      __m128i sum      = _mm_sad_epu8(_mm_andnot_si128(raw, sad_mask), sad_mask);

      std::uint32_t desc       = _mm_cvtsi128_si32(sum);
      std::uint32_t idx_base_3 = desc & 0x1f;
      std::uint32_t popcount   = desc >> 7;

      return {idx_base_3, popcount};
    }
  }

  // See base_3_mask for explanation
  template <std::unsigned_integral T>
  EVE_FORCEINLINE constexpr auto pattern_8_elements(std::array<T, 8> idxs)
  {
    using row = std::array<T, 8>;

    std::array<row, 27> res = {};

    for (unsigned i = 0; i != 27; ++i)
    {
      unsigned number_of_9s = 0, number_of_3s = 0, number_of_1s = 0;
      unsigned base_3_value = i;

      if (base_3_value >= 9) ++number_of_9s, base_3_value -= 9;
      if (base_3_value >= 9) ++number_of_9s, base_3_value -= 9;
      if (base_3_value >= 3) ++number_of_3s, base_3_value -= 3;
      if (base_3_value >= 3) ++number_of_3s, base_3_value -= 3;
      if (base_3_value >= 1) ++number_of_1s, base_3_value -= 1;
      if (base_3_value >= 1) ++number_of_1s, base_3_value -= 1;

      auto* it = res[i].begin();
      if (number_of_1s) *it++ = idxs[0], --number_of_1s;
      if (number_of_1s) *it++ = idxs[1], --number_of_1s;
      if (number_of_3s) *it++ = idxs[2], --number_of_3s;
      if (number_of_3s) *it++ = idxs[3], --number_of_3s;
      if (number_of_9s) *it++ = idxs[4], --number_of_9s;
      if (number_of_9s) *it++ = idxs[5], --number_of_9s;
      *it++ = idxs[6];
      *it++ = idxs[7];
    }

    return res;
  }

  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(ssse3_),
                     unsafe_type,
                     wide<T, N> v,
                     logical<wide<T, N>> mask,
                     Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 8 ) && ( sizeof(T) <= 4 ) &&
             abi_t<T, N>::is_wide_logical
  {
    if constexpr ( sizeof(T) == 4 && current_api == avx ) return compress_store_aggregated_unsafe(v, mask, ptr);
    else
    {
      // First let's reduce the variability in each pair
      auto to_left = eve::slide_left( v, eve::index<1> );
      v = eve::if_else[mask]( v, to_left );

      // This left us with 3 options instead of 4 per each each pair:
      // 00 -> 0 | 01, 10 -> 1 | 11 -> 2
      // On top of this we don't care about the 2 last elements.
      // So we have 3 pairs ^ 3 options = 27 variations.
      //
      // Those variations can be contigious, if we interpret these 0, 1, 2 as a base3 number.

      using u_t = eve::as_integer_t<T, unsigned>;

      alignas(sizeof(T) * N()) const auto patterns = [] {
        if constexpr ( sizeof(T) == 4 ) return pattern_8_elements(idx_dwords<u_t>);
        else                            return pattern_8_elements(idxs_bytes<u_t>);
      }();

      auto [pattern_idx, popcount] = base_3_mask(mask);

      auto         pattern_ptr = eve::as_aligned(patterns[pattern_idx].data(), N());
      wide<u_t, N> pattern {pattern_ptr};

      wide<T, N> shuffled = [&] {
        if constexpr ( sizeof(T) == 4 ) return permvar8(v, pattern);
        else                            return _mm_shuffle_epi8(v, pattern);
      }();

      store(shuffled, ptr);
      return as_raw_pointer(ptr) + popcount;
    }
  }
}
