//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/count_true.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/slide_left.hpp>

#include <eve/arch/top_bits.hpp>

namespace eve::detail
{

  template <typename U, typename N>
  struct do_compress_bmi_avx2
  {
    top_bits<logical<wide<U, N>>> mask;

    static constexpr bool is_1_bits = top_bits<logical<wide<U, N>>>::bits_per_element == 1;
    static constexpr bool is_2_bits = top_bits<logical<wide<U, N>>>::bits_per_element == 2;

    template <kumi::product_type T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      return { kumi::map (*this, v) };
    }

    // Using auto as return type moves the 'not covered case error` into compile time.

    template <typename T>
    auto expanded_mask_8_bytes(std::uint32_t m) const
    {
           if constexpr ( sizeof(T) == 1 && is_1_bits ) return _pdep_u64(m, 0x0101010101010101LL) * 0xff;
      else if constexpr ( sizeof(T) == 1 && is_2_bits ) return _pdep_u64(m, 0x1111111111111111LL) * 0xf;
      else if constexpr ( sizeof(T) == 2 && is_1_bits ) return _pdep_u64(m, 0x0001000100010001LL) * 0xffff;
      else if constexpr ( sizeof(T) == 2 && is_2_bits ) return _pdep_u64(m, 0x0101010101010101LL) * 0xff;
      // 4 and 8 don't fit since we do at least 4 elements.
    }

    template <typename T>
    auto expanded_mask_16_bytes(std::uint32_t m) const
    {
           if constexpr ( sizeof(T) == 1 && is_1_bits ) return _pdep_u64(m, 0x1111111111111111LL) * 0xf;
      else if constexpr ( sizeof(T) == 1 && is_2_bits ) return _pdep_u64(m, 0x3333333333333333LL) * 0x5;
      else if constexpr ( sizeof(T) == 2 && is_1_bits ) return _pdep_u64(m, 0x0101010101010101LL) * 0xff;
      else if constexpr ( sizeof(T) == 2 && is_2_bits ) return _pdep_u64(m, 0x1111111111111111LL) * 0xf;
      else if constexpr ( sizeof(T) == 4 && is_1_bits ) return _pdep_u64(m, 0x0001000100010001LL) * 0xffff;
      else if constexpr ( sizeof(T) == 4 && is_2_bits ) return _pdep_u64(m, 0x0101010101010101LL) * 0xff;
    }

    template <typename T>
    auto expanded_mask_8_qwords(std::uint32_t m) const
    {
           if constexpr ( sizeof(T) == 4 && is_1_bits ) return _pdep_u64(m, 0x0101'0101'0101'0101) * 0xff;
      else if constexpr ( sizeof(T) == 4 && is_2_bits ) return _pdep_u64(m, 0x1111'1111'1111'1111) * 0xf;
      else if constexpr ( sizeof(T) == 8 && is_1_bits ) return _pdep_u64(m, 0x0001'0001'0001'0001) * 0xffff;
      else if constexpr ( sizeof(T) == 8 && is_2_bits ) return _pdep_u64(m, 0x0101'0101'0101'0101) * 0xff;
    }

    template <typename T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      std::uint32_t m = mask.as_int();

      if constexpr ( sizeof(T) * N() <= 8 )
      {
        std::int64_t v_raw    = _mm_cvtsi128_si64 (v);
        std::int64_t m_spread = expanded_mask_8_bytes<T>(m);

        std::int64_t r     = _pext_u64(v_raw, m_spread);

        return _mm_cvtsi64_si128(r);
      }
      else if constexpr ( sizeof(T) * N() == 16 )
      {
        using u8x8 = typename wide<T,N>::template rebind <std::uint8_t,  fixed<8>>;
        using u8x16 = typename wide<T,N>::template rebind <std::uint8_t, fixed<16>>;

        std::uint64_t m_expanded       = expanded_mask_16_bytes<T>(m);
        std::uint64_t compressed_idxes = _pext_u64(0xfedcba9876543210, m_expanded);
        u8x8          half_byte_idx    = _mm_cvtsi64_si128(compressed_idxes);

        // Spread out ab => 0a0b
        auto to_word = eve::convert(half_byte_idx, eve::as<std::uint16_t>{});
        auto pshuvb_mask = ((to_word << 4) | to_word) & (std::uint16_t)0x0f0f;

        u8x16 v_bytes = bit_cast(v, as<u8x16>{});
        v_bytes = _mm_shuffle_epi8(v_bytes, pshuvb_mask);

        return bit_cast(v_bytes, as(v));
      }
      else if constexpr ( sizeof(T) * N() == 32 )
      {
        using u32x8 = typename wide<T,N>::template rebind <std::uint32_t, fixed<8>>;

        std::uint64_t m_expanded       = expanded_mask_8_qwords<T>(m);
        std::uint64_t compressed_idxes = _pext_u64(0x0706050403020100, m_expanded);
        u32x8 to_qwords = _mm256_cvtepu8_epi32(_mm_cvtsi64_si128(compressed_idxes));

        if constexpr ( !std::floating_point<T> ) return _mm256_permutevar8x32_epi32(v, to_qwords);
        else {
          using f32x8 = typename wide<T,N>::template rebind <float, fixed<8>>;
          f32x8 v_floats = bit_cast(v, as<f32x8>{});
          v_floats = _mm256_permutevar8x32_ps(v_floats, to_qwords);
          return bit_cast(v_floats, as(v));
        }
      }
    }
  };

  template <typename U, typename N>
  struct do_compress_bmi_avx512
  {
    top_bits<logical<wide<U, N>>> mask;

    template <kumi::product_type T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      return { kumi::map (*this, v) };
    }

    template <typename T>
    EVE_FORCEINLINE
    wide<T, N> operator()(wide<T, N> v) const
    {
      constexpr auto c = categorize<wide<T, N>>();

      auto m = mask.as_int();

           if constexpr ( match(c, category::float32x4                     ) ) return _mm_maskz_compress_ps      (m, v);
      else if constexpr ( match(c, category::float32x8                     ) ) return _mm256_maskz_compress_ps   (m, v);
      else if constexpr ( match(c, category::int32x4  , category::uint32x4 ) ) return _mm_maskz_compress_epi32   (m, v);
      else if constexpr ( match(c, category::int32x8  , category::uint32x8 ) ) return _mm256_maskz_compress_epi32(m, v);
      else if constexpr ( match(c, category::float64x2                     ) ) return _mm_maskz_compress_pd      (m, v);
      else if constexpr ( match(c, category::float64x4                     ) ) return _mm256_maskz_compress_pd   (m, v);
      else if constexpr ( match(c, category::int64x2  , category::uint64x2 ) ) return _mm_maskz_compress_epi64   (m, v);
      else if constexpr ( match(c, category::int64x4  , category::uint64x4 ) ) return _mm256_maskz_compress_epi64(m, v);
      else if constexpr ( match(c, category::int16x8  , category::uint16x8 ) && N() == 8 )
      {
        auto cvt       = eve::convert(v, eve::as<std::int32_t>{});
        auto cmpressed = (*this)(cvt);
        return eve::convert(cmpressed, eve::as<T>{});
      }
      else
      {
        do_compress_bmi_avx2<U, N> avx2_impl { mask };
        return  avx2_impl(v);
      }
    }
  };

  template<typename T, typename N> constexpr bool compress_bmi_should_split()
  {
    std::size_t max_field_size = kumi::max_flat(T {}, [](auto m) { return sizeof(m); });

         if ( N() > 16  ) return true;
    else if ( N() == 16 ) return max_field_size > 1;
    else if ( N() == 8  ) return max_field_size > 4;
    else                  return false;
  }

  template<typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_using_bmi_(EVE_SUPPORTS(avx2_),
                           wide<T, N> v,
                           top_bits<logical<wide<U, N>>> mask) noexcept
    requires (N() >= 4)
  {
    if constexpr ( compress_bmi_should_split<T, N>() )
    {
      auto [l, h] = v.slice();
      auto [ml, mh] = mask.slice();

      auto lr = compress_using_bmi(l, ml);
      auto hr = compress_using_bmi(h, mh);

      return kumi::cat(lr, hr);
    }
    else
    {
      if constexpr ( current_api >= avx512 ) v = do_compress_bmi_avx512<U, N>{mask}(v);
      else                                   v = do_compress_bmi_avx2  <U, N>{mask}(v);
      kumi::tuple cur {v, count_true(mask)};
      return kumi::tuple<decltype(cur)>{ cur };
    }
  }
}
