//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>
#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>
#include <eve/function/count_true.hpp>

#include <array>
#include <bit>

// sse2/sse3 ---------------------------------------------------------
// switch based implementation

namespace eve::detail
{

  template<relative_conditional_expr C, typename T, typename U>
  EVE_FORCEINLINE
  auto compress_store_impl_switch_4(C c,
                                    wide<T, fixed<4>> v,
                                    logical<wide<U, fixed<4>>> mask
                                    )
  {
    auto [num, count] = compress_store_swizzle_mask_num[c](mask);

    switch (num) {
      case 0b000: { v = v[pattern<3, 0, 0, 0>]; break; }
      case 0b001: { v = v[pattern<0, 3, 0, 0>]; break; }
      case 0b010: { v = v[pattern<1, 3, 0, 0>]; break; }
      case 0b011: { v = v[pattern<0, 1, 3, 0>]; break; }
      case 0b100: { v = v[pattern<2, 3, 0, 0>]; break; }
      case 0b101: { v = v[pattern<0, 2, 3, 0>]; break; }
      case 0b110: { v = v[pattern<1, 2, 3, 0>]; break; }
      case 0b111: {                             break; }
      #if defined(SPY_COMPILER_IS_CLANG) or defined(SPY_COMPILER_IS_GCC)
      default: __builtin_unreachable();
      #endif
    }

    return std::pair{v, count};
  }

  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse2_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 ) && (current_api < ssse3)
  {
    int count;
    if constexpr ( sizeof(T) == 1 )
    {
      // We have to convert to shorts here. Does not optimise well without.
      auto shorts = convert(v, eve::as<std::uint16_t>{});
      auto [shuffled, count_] = compress_store_impl_switch_4(c, shorts, mask);
      v = eve::convert(shuffled, eve::as<T>{});
      count = count_;
    }
    else
    {
      auto [shuffled, count_] = compress_store_impl_switch_4(c, v, mask);
      v = shuffled;
      count = count_;
    }

    store(v, ptr);
    return as_raw_pointer(ptr) + count;
  }

}

// ssse3 -> avx2 (no bmi) ---------------------------------------------------------
// mask based (@aqrit from StackOverflow's idea)

/*
  NOTE:
    We have 3 implementations: 4 elements, 8 elements and 16 elements.
    For 4 elements we can process ignore better, utilizing top_bits.
    For every other case since we do a shift + & we have to use the mask => we use the base case.

    At the moment we don't have an avx-512 implementation, since the logical is different.
*/

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
  constexpr auto idxs_dwords = [] {
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

  template <std::unsigned_integral T>
  constexpr auto pattern_4_elements_bytes_with_popcounts_v alignas(sizeof(T) * 4) =
    add_popcounts(pattern_4_elements_bytes_v<T>);

  template <std::unsigned_integral T>
  constexpr auto pattern_4_elements_dwords_v alignas(sizeof(T) * 4) =
    pattern_4_elements(idxs_dwords<T>);

  template <std::unsigned_integral T>
  constexpr auto pattern_8_elements_dwords_v alignas(sizeof(T) * 8) =
    pattern_8_elements(idxs_dwords<T>);

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
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
         if ( C::is_complete && !C::is_inverted ) return as_raw_pointer(ptr);
    else if constexpr ( sizeof(T) == 8 && current_api == avx  )
    {
      return compress_store_impl_(EVE_RETARGET(cpu_), c, v, mask, ptr);
    }
    else if constexpr ( sizeof(T) == 8 )
    {
      auto [num, count] = compress_store_swizzle_mask_num[c](mask);
      std::uint64_t const* raw_pattern_ptr = pattern_4_elements_dwords_v<std::uint64_t>[num].data();
      aligned_ptr<std::uint64_t const, eve::fixed<4>> pattern_ptr{raw_pattern_ptr};
      wide<std::uint32_t, eve::fixed<8>> pattern{ptr_cast<std::uint32_t>(pattern_ptr)};

      wide<T, N> shuffled = permvar8(v, pattern);

      store(shuffled, ptr);
      return as_raw_pointer(ptr) + count;
    }
    else if constexpr ( std::floating_point<T> )
    {
      using i_t = eve::as_integer_t<T>;
      auto  i_p = ptr_cast<i_t>(ptr);
      auto  i_v = eve::bit_cast(v, eve::as<wide<i_t, N>>{});

      i_t* stored = compress_store_impl(c, i_v, mask, i_p);
      return (T*) stored;
    }
    else
    {
      using u_t         = eve::as_integer_t<T, unsigned>;
      using bytes_fixed = eve::fixed<N() * sizeof(T)>;
      using bytes_t = typename wide<T, N>::template rebind<std::uint8_t, bytes_fixed>;

      auto [num, count] = compress_store_swizzle_mask_num[c](mask);

      using a_p = aligned_ptr<u_t const, N>;
      u_t const* raw_pattern_ptr = pattern_4_elements_bytes_v<u_t>[num].data();
      bytes_t pattern(ptr_cast<std::uint8_t const>( a_p(raw_pattern_ptr) ));

      wide<T, N> shuffled = _mm_shuffle_epi8(v, pattern);
      store(shuffled, ptr);

      return as_raw_pointer(ptr) + count;
    }
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
    if constexpr ( N() == 4 && sizeof(T) == 8 && current_api == avx  )
    {
      return compress_store_impl_aggregated(v, mask, ptr);
    }
    else return compress_store_impl[eve::ignore_none](v, mask, ptr);
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && (current_api <= avx2) && ( N() == 8 )
  {
    if constexpr ( sizeof(T) == 4 && current_api == avx ) return compress_store_impl_aggregated(v, mask, ptr);
    else
    {
      // First let's reduce the variability in each pair
      eve::wide<T, N> to_left = [&] {
             if constexpr ( std::floating_point<T> ) return _mm256_permute_ps   (v, _MM_SHUFFLE(0, 3, 2, 1));
        else if constexpr ( sizeof(T) == 4         ) return _mm256_shuffle_epi32(v, _MM_SHUFFLE(0, 3, 2, 1));
        else                                         return _mm_bsrli_si128     (v, sizeof(T));
      }();
      v = eve::if_else[mask]( v, to_left );

      // This left us with 3 options instead of 4 per each each pair:
      // 00 -> 0 | 01, 10 -> 1 | 11 -> 2
      // On top of this we don't care about the 2 last elements.
      // So we have 3 pairs ^ 3 options = 27 variations.
      //
      // Those variations can be contiguous, if we interpret these 0, 1, 2 as a base3 number.

      using u_t = eve::as_integer_t<T, unsigned>;

      auto [pattern_idx, popcount] = compress_store_swizzle_mask_num(mask);

      const auto* raw_pattern_ptr = [](int idx) {
        if constexpr ( sizeof(T) == 4 ) return pattern_8_elements_dwords_v<u_t>[idx].data();
        else                            return pattern_8_elements_bytes_v<u_t> [idx].data();
      }(pattern_idx);

      wide<u_t, N> pattern {eve::as_aligned(raw_pattern_ptr, N())};

      wide<T, N> shuffled = [&] {
        if constexpr ( sizeof(T) == 4 ) return permvar8(v, pattern);
        else                            return _mm_shuffle_epi8(v, pattern);
      }();

      store(shuffled, ptr);
      return as_raw_pointer(ptr) + popcount;
    }
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && (current_api <= avx2) && ( N() == 16 )
  {
    using half_wide = wide<T, eve::fixed<8>>;

    if constexpr ( sizeof(T) == 2 )
    {
      auto [l, h] = [&] {
        if constexpr ( current_api == avx2 )
        {
          wide<T, N> to_left =  _mm256_shufflehi_epi16(v,       _MM_SHUFFLE(0, 3, 2, 1));
                     to_left =  _mm256_shufflelo_epi16(to_left, _MM_SHUFFLE(0, 3, 2, 1));
          v = eve::if_else[mask](v, to_left);
          return v.slice();
        }
        else
        {
          auto [l, h] = v.slice();
          auto [ml, mh] = mask.slice();
          half_wide l_to_left = _mm_bsrli_si128(l, 2);
          half_wide h_to_left = _mm_bsrli_si128(h, 2);
          l = eve::if_else[ml](l, l_to_left);
          h = eve::if_else[mh](h, h_to_left);
          return std::pair{l, h};
        }
      }();

      using pattern8 = typename wide<T, N>::template rebind<std::uint16_t, eve::fixed<8>>;

      auto [lo_idx, lo_count, hi_idx, hi_count] = compress_store_swizzle_mask_num(mask);

      auto lo_shuffle_ptr = eve::as_aligned(pattern_8_elements_bytes_v<std::uint16_t>[lo_idx].data(), eve::lane<8>);
      auto hi_shuffle_ptr = eve::as_aligned(pattern_8_elements_bytes_v<std::uint16_t>[hi_idx].data(), eve::lane<8>);

      pattern8 lo_shuffle{lo_shuffle_ptr};
      pattern8 hi_shuffle{hi_shuffle_ptr};

      l = _mm_shuffle_epi8(l, lo_shuffle);
      h = _mm_shuffle_epi8(h, hi_shuffle);
      eve::store(l, ptr);

      T* res = as_raw_pointer(ptr) + lo_count;
      eve::store(h, res);
      return res + hi_count;
    }
    else if constexpr ( sizeof(T) == 1 )
    {
      using pattern8 = typename wide<T, N>::template rebind<std::uint8_t, eve::fixed<8>>;

      eve::wide<T, N> to_left = _mm_bsrli_si128(v, 1);
      v = eve::if_else[mask]( v, to_left );

      auto [lo_idx, lo_count, hi_idx, hi_count] = compress_store_swizzle_mask_num(mask);

      pattern8 lo_shuffle{pattern_8_elements_bytes_v<std::uint8_t>[lo_idx].data()};
      pattern8 hi_shuffle{pattern_8_elements_bytes_v<std::uint8_t>[hi_idx].data()};
      hi_shuffle |= pattern8{0x08};  // adjust higher idxs +8

      T* res = as_raw_pointer(ptr);
      _mm_storel_epi64((__m128i*)res, _mm_shuffle_epi8(v, lo_shuffle));
      res += lo_count;
      _mm_storel_epi64((__m128i*)res, _mm_shuffle_epi8(v, hi_shuffle));
      return res + hi_count;
    }
  }
}
