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
  EVE_FORCEINLINE constexpr auto pattern_4_elements(std::array<T, 4> idxs)
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

  template <typename Row, std::size_t N>
  EVE_FORCEINLINE constexpr auto add_popcounts(std::array<Row, N> patterns)
  {
    for (std::uint8_t i = 0; i != patterns.size(); ++i) {
      patterns[i][0] = add_popcount(patterns[i][0], std::popcount(i));
    }
    return patterns;
  }


  // The idea from: https://gist.github.com/aqrit/6e73ca6ff52f72a2b121d584745f89f3#file-despace-cpp-L141
  // Was shown to me by: @aqrit
  // Stack Overflow discussion: https://chat.stackoverflow.com/rooms/212510/discussion-between-denis-yaroshevskiy-and-peter-cordes
  EVE_FORCEINLINE constexpr auto char_4_patterns()
  {
    constexpr std::array idxs = {
      std::uint8_t{0x00}, std::uint8_t{0x01}, std::uint8_t{0x02}, std::uint8_t{0x03}
    };
    return pattern_4_elements(idxs);
  }

  EVE_FORCEINLINE constexpr auto int_32_4_patterns()
  {
    constexpr std::array idxs = {0x03020100u, 0x07060504u, 0x0b0a0908u, 0x0f0e0d0cu};
    return pattern_4_elements(idxs);
  }

  EVE_FORCEINLINE constexpr auto int_64_4_patterns()
  {
    auto u64_idx = [](unsigned low, unsigned high) { return (uint64_t{high} << 32) | low; };
    constexpr std::array idxs = { u64_idx(0, 1), u64_idx(2, 3), u64_idx(4, 5), u64_idx(6, 7) };
    return pattern_4_elements(idxs);
  }

  template <typename T, typename N>
  EVE_FORCEINLINE wide<T, N> permvar8(wide<T, N> v, __m256i pattern)
    requires (current_api >= avx2)
  {
    if constexpr ( std::floating_point<T> ) return _mm256_permutevar8x32_ps   (v, pattern);
    else                                    return _mm256_permutevar8x32_epi32(v, pattern);
  }

  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(ssse3_),
                     unsafe_type u,
                     wide<T, N> v,
                     logical<wide<T, N>> mask,
                     Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>>
  {
    if constexpr ( N() == 4 && sizeof(T) == 8 && current_api >= avx2 )
    {
      alignas(32) auto patterns = int_64_4_patterns();

      top_bits mmask{mask};
      aligned_ptr<std::uint64_t, 32> pattern_ptr{patterns[mmask.as_int() & 7].data()};
      wide<std::uint32_t, eve::fixed<8>> pattern{ptr_cast<std::uint32_t>(pattern_ptr)};

      wide<T, N> shuffled = permvar8(v, pattern);

      store(shuffled, ptr);
      int popcount = eve::count_true(mask);
      return as_raw_pointer(ptr) + popcount;
    }
    else if constexpr ( std::same_as<abi_t<T, N>, x86_256_> )
    {
      return compress_store_aggregated_unsafe(v, mask, ptr);
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
    else if constexpr ( N() == 4 && sizeof(T) == 4 )
    {
      alignas(16) auto patterns = add_popcounts(int_32_4_patterns());

      top_bits mmask{mask};

      aligned_ptr<std::uint32_t, 16> pattern_ptr{patterns[mmask.as_int() & 7].data()};
      wide<std::uint32_t, eve::fixed<4>> pattern{pattern_ptr};

      wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);

      auto byte_idxs = eve::bit_cast(pattern, eve::as_<wide<std::uint8_t, eve::fixed<16>>>{});
      int popcount = get_popcount(byte_idxs.get(0)) + mmask.get(3);

      store(shuffled, ptr);
      return as_raw_pointer(ptr) + popcount;
    }
    else if constexpr ( N() == 4 && sizeof(T) == 1 )
    {
      auto patterns = add_popcounts(char_4_patterns());

      top_bits mmask{mask};
      wide<std::uint8_t, eve::fixed<4>> pattern{patterns[mmask.as_int() & 7].data()};

      wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);
      store(shuffled, ptr);

      int popcount = get_popcount(pattern.get(0)) + mmask.get(3);
      return as_raw_pointer(ptr) + popcount;
    }
    else return compress_store_(EVE_RETARGET(cpu_), u, v, mask, ptr);
  }
}
