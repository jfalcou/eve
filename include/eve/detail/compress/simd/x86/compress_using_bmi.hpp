//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>
#include <eve/function/count_true.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/slide_left.hpp>

#include <eve/detail/top_bits.hpp>

namespace eve::detail
{

  template <typename U, typename N>
  struct do_compress_bmi_avx2
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

      std::uint32_t m = mask.as_int();

      if constexpr ( match(c, category::int8x16, category::uint8x16 ) && N() <= 8 )
      {
        std::int64_t v_raw = _mm_cvtsi128_si64 (v);
        std::int64_t m_spread = _pdep_u64(m, 0x0101010101010101LL) * 0xff;
        std::int64_t r     = _pext_u64(v_raw, m_spread);

        return _mm_cvtsi64_si128(r);
      }
      else if constexpr ( match(c, category::int8x16, category::uint8x16 ) )
      {
        using u8x8 = typename wide<T,N>::template rebind <std::uint8_t, fixed<8>>;

        std::uint64_t m_expanded       = _pdep_u64(m, 0x1111111111111111) * 0xf;
        std::uint64_t compressed_idxes = _pext_u64(0xfedcba9876543210, m_expanded);
        u8x8           half_byte_idx   = _mm_cvtsi64_si128(compressed_idxes);

        // Spread out ab => 0a0b
        auto to_word = eve::convert(half_byte_idx, eve::as<std::uint16_t>{});
        auto pshuvb_mask = ((to_word << 4) | to_word) & (std::uint16_t)0x0f0f;

        return _mm_shuffle_epi8(v, pshuvb_mask);
      }
    }

  };

  template <typename U, typename N>
  struct do_compress_bmi
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
      else if constexpr ( match(c, category::int16x8  , category::uint16x8 ) )
      {
        std::int64_t v_raw    = _mm_cvtsi128_si64 (v);
        std::int64_t m_spread = _pdep_u64(m, 0x0001'0001'0001'0001LL) * 0xffff;
        std::int64_t r        = _pext_u64(v_raw, m_spread);

        return _mm_cvtsi64_si128(r);
      }
      else if constexpr ( match(c, category::int8x16, category::uint8x16 ) )
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
  auto compress_using_bmi_(EVE_SUPPORTS(avx512_),
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
      v = do_compress_bmi<U, N>{mask}(v);
      kumi::tuple cur {v, detail::count_true(mask)};
      return kumi::tuple<decltype(cur)>{ cur };
    }
  }
}
