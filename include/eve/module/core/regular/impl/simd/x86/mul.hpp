//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/module/core/regular/combine.hpp>

namespace eve::detail
{
  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE upgrade_t<wide<T, N>> mul_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
  requires (x86_abi<abi_t<T, N>> && O::contains(widen))
  {
    return mul.behavior(cpu_{}, opts, v, w);
  }

  template<callable_options O, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires (x86_abi<abi_t<T, N>> && !O::contains(mod)&& !O::contains(widen))
  {
    constexpr auto c = categorize<wide<T, N>>();
    if constexpr(floating_value<T> && (O::contains(lower) || O::contains(upper)))
    {
      if constexpr (O::contains(strict) || (current_api < avx512))
      {
        return mul.behavior(cpu_{}, opts, a, b);
      }
      else
      {
        auto constexpr dir = (O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) | _MM_FROUND_NO_EXC;
        if      constexpr ( c == category::float64x8  ) return _mm512_mul_round_pd(a, b, dir);
        else if constexpr ( c == category::float32x16 ) return _mm512_mul_round_ps(a, b, dir);
        else if constexpr ( c == category::float64x4 || c == category::float64x2 ||
                            c == category::float32x8 || c == category::float32x4 || c == category::float32x2)
        {
          auto aa = eve::combine(a, a);
          auto bb = eve::combine(b, b);
          auto aapbb = mul[opts](aa, bb);
          return slice(aapbb, eve::upper_);
        }
        else
        {
          return mul.behavior(cpu_{}, opts, a, b);
        }
     }
    }
    else if constexpr (O::contains(saturated) && std::integral<T>)
    {
      return mul.behavior(cpu_{}, opts, a, b);
    }
    else
    {
      if constexpr( c == category::float64x8  ) return _mm512_mul_pd(a, b);
      else  if constexpr( c == category::float64x4  ) return _mm256_mul_pd(a, b);
      else  if constexpr( c == category::float64x2  ) return _mm_mul_pd(a, b);
      else  if constexpr( c == category::float32x16 ) return _mm512_mul_ps(a, b);
      else  if constexpr( c == category::float32x8  ) return _mm256_mul_ps(a, b);
      else  if constexpr( c == category::float32x4  ) return _mm_mul_ps(a, b);
      else  if constexpr( c == category::int64x8    ) return _mm512_mullo_epi64(a, b);
      else  if constexpr( c == category::uint64x8   ) return _mm512_mullo_epi64(a, b);
      else  if constexpr( c == category::int32x16   ) return _mm512_mullo_epi32(a, b);
      else  if constexpr( c == category::uint32x16  ) return _mm512_mullo_epi32(a, b);
      else  if constexpr(((c == category::int32x8) || (c == category::uint32x8)) && (current_api >= avx2))
      {
        return _mm256_mullo_epi32(a, b);
      }
      else  if constexpr ((c == category::int32x4) || (c == category::uint32x4))
      {
        if constexpr (current_api >= sse4_1)
        {
          return _mm_mullo_epi32(a, b);
        }
        else
        {
          static constexpr auto half_size = ((N::value / 2) > 0) ? N::value / 2 : 1;
          using htype  = wide<std::int64_t, fixed<half_size>>;

          htype mhi    = _mm_setr_epi32(-1, 0, -1, 0);
          htype mlo    = mhi;
          auto  la     = _mm_srli_si128(a, 4);
          auto  lb     = _mm_srli_si128(b, 4);

          mhi &= htype {_mm_mul_epu32(a, b)};
          mlo &= htype {_mm_mul_epu32(la, lb)};
          mhi |= htype {_mm_slli_si128(mlo, 4)};

          return mhi.storage();
        }
      }
      else  if constexpr((c == category::int16x16 || c == category::uint16x16) && current_api >= avx2)
      {
        return _mm256_mullo_epi16(a, b);
      }
      else  if constexpr( c == category::int16x32   ) return _mm512_mullo_epi16(a, b);
      else  if constexpr( c == category::uint16x32  ) return _mm512_mullo_epi16(a, b);
      else  if constexpr( c == category::int16x8    ) return _mm_mullo_epi16(a, b);
      else  if constexpr( c == category::uint16x8   ) return _mm_mullo_epi16(a, b);
      else  if constexpr ((c == category::int8x16) || (c == category::uint8x16))
      {
        static constexpr auto half_size = ((N::value / 2) > 0) ? N::value / 2 : 1;

        using htype  = wide<std::int16_t, fixed<half_size>>;

        htype mhi    = _mm_set1_epi16(0x00FF);
        htype mlo    = mhi;
        auto  la  = _mm_srli_epi16(a, 8);
        auto  lb = _mm_srli_epi16(b, 8);

        mhi &= htype {_mm_mullo_epi16(a, b)};
        mlo &= htype {_mm_mullo_epi16(la, lb)};
        mhi |= htype {_mm_slli_epi16(mlo, 8)};

        return mhi.storage();
      }
      else
      {
        auto s = a;
        constexpr auto smul = [](auto va, auto vb) { return va * vb; };

        if constexpr (N::value >= 2) return aggregate(smul, s, b);
        else                         return map(smul, s, b);
      }
    }
  }

  template<callable_options O, conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE wide<T, N> mul_(EVE_REQUIRES(avx512_), C const& cx, O const& opts, wide<T, N> a, wide<T, N> b) noexcept
  requires (x86_abi<abi_t<T, N>> && !O::contains(mod)&& !O::contains(widen))
  {
    constexpr auto c = categorize<wide<T, N>>();

    auto src = alternative(cx, a, as<wide<T, N>> {});
    auto m   = expand_mask(cx, as<wide<T, N>> {}).storage().value;

    if constexpr (floating_value<T> && (O::contains(lower) || O::contains(upper)))
    {
      if constexpr (O::contains(strict))
      {
        return mul[opts][cx].retarget(cpu_{}, a, b);
      }
      else
      {
        auto constexpr dir = (O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) | _MM_FROUND_NO_EXC;
        if      constexpr ( c == category::float64x8  ) return _mm512_mask_mul_round_pd(src, m, a, b, dir);
        else if constexpr ( c == category::float32x16 ) return _mm512_mask_mul_round_ps(src, m, a, b, dir);
        else if constexpr ( c == category::float64x4 || c == category::float64x2 ||
                            c == category::float32x8 || c == category::float32x4 || c == category::float32x2)
        {
          auto aa = eve::combine(a, a);
          auto bb = eve::combine(b, b);
          auto aapbb = mul[opts](aa, bb);
          auto s = slice(aapbb, eve::upper_);
          return if_else(cx, s, src);
        }
        else
        {
          return mul[opts][cx].retarget(cpu_{}, a, b);
        }
      }
    }
    else if constexpr(O::contains(saturated))
    {
      return mul[opts][cx].retarget(cpu_{}, a, b);
    }
    else
    {
      if      constexpr( c == category::float32x16) return _mm512_mask_mul_ps   (src, m, a, b);
      else if constexpr( c == category::float32x8 ) return _mm256_mask_mul_ps   (src, m, a, b);
      else if constexpr( c == category::float32x4 ) return _mm_mask_mul_ps      (src, m, a, b);
      else if constexpr( c == category::float64x8 ) return _mm512_mask_mul_pd   (src, m, a, b);
      else if constexpr( c == category::float64x4 ) return _mm256_mask_mul_pd   (src, m, a, b);
      else if constexpr( c == category::float64x2 ) return _mm_mask_mul_pd      (src, m, a, b);
      else                                          return mul[opts][cx].retarget(cpu_{}, a, b);
    }
  }
}
