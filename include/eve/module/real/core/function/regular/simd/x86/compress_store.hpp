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
  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(ssse3_),
                     unsafe_type,
                     wide<T, N> v,
                     logical<wide<T, N>> mask,
                     Ptr ptr) noexcept
    requires std::same_as<abi_t<T, N>, x86_128_> && (N() == 4)
  {
    if constexpr ( std::floating_point<T> )
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

      alignas(sizeof(T) * 4) const auto patterns = add_popcounts(pattern_4_elements([]{
             if constexpr ( sizeof(T) == 4 ) return std::array{0x03020100u, 0x07060504u, 0x0b0a0908u, 0x0f0e0d0cu};
        else if constexpr ( sizeof(T) == 2 ) return std::array{u_t{0x0100}, u_t{0x0302}, u_t{0x0504}, u_t{0x0706}};
        else if constexpr ( sizeof(T) == 1 ) return std::array{u_t{0x00},   u_t{0x01},   u_t{0x02},   u_t{0x03}};
      }()));

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

      using a_p = aligned_ptr<u_t const, N() * sizeof(u_t)>;
      bytes_t pattern { ptr_cast<std::uint8_t const>( a_p{patterns[mmask & 7].data()} )};

      wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);
      store(shuffled, ptr);

      int popcount = get_popcount(pattern.get(0)) + (bool)(mmask & 8);
      return as_raw_pointer(ptr) + popcount;
    }
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

  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(avx_),
                     unsafe_type,
                     wide<T, N> v,
                     logical<wide<T, N>> mask,
                     Ptr ptr) noexcept
    requires std::same_as<abi_t<T, N>, x86_256_> && (N() == 4)
  {
    if constexpr ( N() == 4 && sizeof(T) == 8 && current_api >= avx2 )
    {
      alignas(32) auto patterns = [] {
        auto u64_idx = [](unsigned low, unsigned high) { return (uint64_t{high} << 32) | low; };
        constexpr std::array idxs = { u64_idx(0, 1), u64_idx(2, 3), u64_idx(4, 5), u64_idx(6, 7) };
        return pattern_4_elements(idxs);
      }();

      top_bits mmask{mask};
      aligned_ptr<std::uint64_t, 32> pattern_ptr{patterns[mmask.as_int() & 7].data()};
      wide<std::uint32_t, eve::fixed<8>> pattern{ptr_cast<std::uint32_t>(pattern_ptr)};

      wide<T, N> shuffled = permvar8(v, pattern);

      store(shuffled, ptr);
      int popcount = eve::count_true(mask);
      return as_raw_pointer(ptr) + popcount;
    }
    else return compress_store_aggregated_unsafe(v, mask, ptr);
  }
}
