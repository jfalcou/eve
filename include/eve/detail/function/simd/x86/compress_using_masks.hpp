//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

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

  template <typename T, typename N>
  EVE_FORCEINLINE
  auto compress_using_masks_shuffle_(EVE_SUPPORTS(avx2_), wide<T, N> v, std::ptrdiff_t num) noexcept
    requires ( std::same_as<abi_t<T, N>, x86_256_> )
  {
    using u_t = eve::as_integer_t<T, unsigned>;

    if constexpr ( N() == 4 )
    {
      u_t const* pattern_p = pattern_4_elements_dwords_v<u_t>[num].data();

      wide<u_t, N> pattern { eve::as_aligned(pattern_p, N()) };
      return permvar8(v, pattern);
    }
    else if constexpr ( N() == 8 )
    {
      u_t const* pattern_p = pattern_8_elements_dwords_v<u_t>[num].data();

      wide<u_t, N> pattern {eve::as_aligned(pattern_p, N())};
      return permvar8(v, pattern);
    }
  }


  template <typename T, typename N>
  EVE_FORCEINLINE
  auto compress_using_masks_to_left_(EVE_SUPPORTS(avx_), wide<T, N> v)
    requires ( std::same_as<abi_t<T, N>, x86_256_> && sizeof(T) <= 4 )
  {
         if constexpr ( std::floating_point<T>                ) return _mm256_permute_ps   (v, _MM_SHUFFLE(0, 3, 2, 1));
    else if constexpr ( sizeof(T) == 4                        ) return _mm256_shuffle_epi32(v, _MM_SHUFFLE(0, 3, 2, 1));
    else if constexpr ( sizeof(T) == 2 && current_api == avx2 )
    {
      v = _mm256_shufflehi_epi16(v, _MM_SHUFFLE(0, 3, 2, 1));
      v = _mm256_shufflelo_epi16(v, _MM_SHUFFLE(0, 3, 2, 1));
      return v;
    }
    else if constexpr ( sizeof(T) == 2 )
    {
      auto [l, h] = v.slice();
      l = _mm_bsrli_si128(l, 2);
      h = _mm_bsrli_si128(h, 2);
      return wide<T, N>{l, h};
    }
    else compress_using_masks_to_left_(EVE_RETARGET(cpu_), v);
  }

  struct compress_using_masks_shuffle_16
  {
    std::ptrdiff_t lo_idx, hi_idx;

    template <typename T, typename N>
    EVE_FORCEINLINE auto operator()(wide<T, N> v) const
    {
      using half_wide = wide<T, eve::fixed<N() / 2>>;

      if constexpr ( kumi::product_type<T> )
      {
        auto mapped = kumi::map(*this, v);
        auto first  = kumi::map([](auto pair) { return get<0>(pair); }, mapped);
        auto second = kumi::map([](auto pair) { return get<1>(pair); }, mapped);
        return kumi::tuple{half_wide{first}, half_wide{second}};
      }
      else
      {
        using u_t = eve::as_integer_t<T, unsigned>;
        using pattern8 = wide<u_t, eve::fixed<8>>;

        auto lo_shuffle_ptr = eve::as_aligned(pattern_8_elements_bytes_v<u_t>[lo_idx].data(), eve::lane<8>);
        auto hi_shuffle_ptr = eve::as_aligned(pattern_8_elements_bytes_v<u_t>[hi_idx].data(), eve::lane<8>);

        pattern8 lo_shuffle{lo_shuffle_ptr};
        pattern8 hi_shuffle{hi_shuffle_ptr};

        if constexpr (sizeof(T) == 1)
        {
          hi_shuffle |= pattern8{0x08};  // adjust higher idxs +8

          half_wide l = _mm_shuffle_epi8(v, lo_shuffle);
          half_wide h = _mm_shuffle_epi8(v, hi_shuffle);

          return kumi::tuple{l, h};
        }
        else
        {
          auto [l, h] = v.slice();

          l = _mm_shuffle_epi8(l, lo_shuffle);
          h = _mm_shuffle_epi8(h, hi_shuffle);

          return kumi::tuple{l, h};
        }
      }
    }
  };


  template <typename T, typename N, typename U>
  EVE_FORCEINLINE
  auto compress_using_masks_(EVE_SUPPORTS(ssse3_), ignore_none_ c, wide<T, N> v, logical<wide<U, N>> mask)
    requires ( N() == 16 ) && (max_scalar_size_v<T> <= 2)
  {
    if constexpr ( max_scalar_size_v<T> == 2 && current_api < avx ) return compress_using_masks_(EVE_RETARGET(cpu_), c, v, mask);
    else
    {
      v = eve::if_else[mask]( v, compress_using_masks_to_left( v ) );
      auto [lo_idx, lo_count, hi_idx, hi_count] = compress_store_swizzle_mask_num(mask);

      auto [shuffled_lo, shuffled_hi] = compress_using_masks_shuffle_16{lo_idx, hi_idx}(v);

      return kumi::tuple{ kumi::tuple{shuffled_lo, lo_count}, kumi::tuple{ shuffled_hi, hi_count } };
    }
  }

}
