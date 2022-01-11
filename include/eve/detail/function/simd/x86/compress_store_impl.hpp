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
#include <eve/function/unalign.hpp>

#include <eve/detail/function/compress_store_impl_switch.hpp>

#include <array>
#include <bit>

// sse2/sse3 ---------------------------------------------------------
// switch based implementation

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse2_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires (current_api < ssse3)
  {
    return compress_store_impl_switch[c](v, mask, ptr);
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
  T* compress_store_impl_(EVE_SUPPORTS(sse4_1_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
         if ( C::is_complete && !C::is_inverted ) return unalign(ptr);
    else if constexpr ( sizeof(T) == 8 && current_api == avx  )
    {
      return compress_store_impl_(EVE_RETARGET(cpu_), c, v, mask, ptr);
    }
    else if constexpr ( std::same_as<T, float> )
    {
      auto  u_p = ptr_cast<std::uint32_t>(ptr);
      auto  u_v = eve::bit_cast(v, eve::as<wide<std::uint32_t, N>>{});

      std::uint32_t* stored = compress_store_impl(c, u_v, mask, u_p);
      return (float*) stored;
    }
    else
    {
      using u_t = eve::as_integer_t<T, unsigned>;

      auto [num, count] = compress_store_swizzle_mask_num[c](mask);

      const auto* raw_pattern_ptr = [](int idx) {
        if constexpr ( sizeof(T) == 8 ) return pattern_4_elements_dwords_v<u_t>[idx].data();
        else                            return pattern_4_elements_bytes_v<u_t> [idx].data();
      }(num);

      wide<u_t, N> pattern {eve::as_aligned(raw_pattern_ptr, N())};

      wide<T, N> shuffled = [&] {
        if constexpr ( sizeof(T) == 8 ) return permvar8(v, pattern);
        else                            return _mm_shuffle_epi8(v, pattern);
      }();

      store(shuffled, ptr);
      return unalign(ptr) + count;
    }
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse4_1_),
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
      return unalign(ptr) + popcount;
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

      T* res = unalign(ptr) + lo_count;
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

      T* res = unalign(ptr);
      _mm_storel_epi64((__m128i*)res, _mm_shuffle_epi8(v, lo_shuffle));
      res += lo_count;
      _mm_storel_epi64((__m128i*)res, _mm_shuffle_epi8(v, hi_shuffle));
      return res + hi_count;
    }
  }
}
