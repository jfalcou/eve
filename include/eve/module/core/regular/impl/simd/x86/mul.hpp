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
#include <eve/module/core.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/combine.hpp>
#include <eve/module/core/regular/lohi.hpp>
#include <eve/wide.hpp>

#include <cstdint>
#include <emmintrin.h>
#include <immintrin.h>

#include <type_traits>

struct M128iPair
{
  __m128i lo;
  __m128i hi;
};

// Helper to split 64-bit lanes into 32-bit low and high parts
M128iPair split_lohi(__m128i v) {

  using w64u = eve::wide<std::uint64_t, eve::fixed<2>, eve::sse2_>;

  w64u vec = eve::bit_cast(v, eve::as<w64u>{});
  w64u lo = vec & w64u(0x00000000FFFFFFFFULL);
  w64u hi = vec >> 32;

  return {
      eve::bit_cast(lo, eve::as<__m128i>{}),
      eve::bit_cast(hi, eve::as<__m128i>{})
  };
}
// Multiply two 128-bit vectors with 32-bit integers template
template <typename T>
EVE_FORCEINLINE __m128i mul32x32(__m128i a, __m128i b) {
  using w32 = eve::wide<std::conditional_t<std::is_signed_v<T>, std::int32_t, std::uint32_t>, eve::fixed<4>, eve::sse2_>;

  return eve::bit_cast(
      eve::mul(
          eve::bit_cast(a, eve::as<w32>{}),
          eve::bit_cast(b, eve::as<w32>{})),
      eve::as<__m128i>{});
}
namespace eve::detail
{
template<callable_options O, typename T, typename N>
EVE_FORCEINLINE upgrade_t<wide<T, N>>
                mul_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> v, wide<T, N> w) noexcept
requires(x86_abi<abi_t<T, N>> && O::contains(widen))
{
  return mul.behavior(cpu_ {}, opts, v, w);
}

template<callable_options O, typename T, typename N>
EVE_FORCEINLINE wide<T, N>
                mul_(EVE_REQUIRES(sse2_), O const& opts, wide<T, N> a, wide<T, N> b) noexcept
requires(x86_abi<abi_t<T, N>> && !O::contains(mod) && !O::contains(widen))
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( floating_value<T> && (O::contains(lower) || O::contains(upper)) )
  {
    if constexpr( O::contains(strict) || (current_api < avx512) )
    {
      return mul.behavior(cpu_ {}, opts, a, b);
    }
    else
    {
      auto constexpr dir =
          (O::contains(lower) ? _MM_FROUND_TO_NEG_INF : _MM_FROUND_TO_POS_INF) | _MM_FROUND_NO_EXC;
      if constexpr( c == category::float64x8 ) return _mm512_mul_round_pd(a, b, dir);
      else if constexpr( c == category::float32x16 ) return _mm512_mul_round_ps(a, b, dir);
      else if constexpr( c == category::float64x4 || c == category::float64x2
                         || c == category::float32x8 || c == category::float32x4
                         || c == category::float32x2 )
      {
        auto aa    = eve::combine(a, a);
        auto bb    = eve::combine(b, b);
        auto aapbb = mul[opts](aa, bb);
        return slice(aapbb, eve::upper_);
      }
      else { return mul.behavior(cpu_ {}, opts, a, b); }
    }
  }
  else if constexpr( O::contains(saturated) && std::integral<T> )
  {
    return mul.behavior(cpu_ {}, opts, a, b);
  }
  else
  {
    if constexpr( c == category::float64x8 ) return _mm512_mul_pd(a, b);
    else if constexpr( c == category::float64x4 ) return _mm256_mul_pd(a, b);
    else if constexpr( c == category::float64x2 ) return _mm_mul_pd(a, b);
    else if constexpr( c == category::float32x16 ) return _mm512_mul_ps(a, b);
    else if constexpr( c == category::float32x8 ) return _mm256_mul_ps(a, b);
    else if constexpr( c == category::float32x4 ) return _mm_mul_ps(a, b);
    else if constexpr( c == category::int64x8 ) return _mm512_mullo_epi64(a, b);
    else if constexpr( c == category::int64x4 )
    {
      // If AVX-512; use its direct 64-bit multiplication instruction
      if constexpr( eve::current_api >= eve::avx512 ) { return _mm256_mullo_epi64(a, b); }
      else if constexpr( eve::current_api == eve::avx2 )
      {
        // Split 256-bit vectors into 128-bit halves
        auto a_lo = a.slice(eve::lower_);
        auto a_hi = a.slice(eve::upper_);
        auto b_lo = b.slice(eve::lower_);
        auto b_hi = b.slice(eve::upper_);

        // Split each 64-bit integer into 32-bit low and high parts
        auto [al_low, ah_low]   = split_lohi(a_lo);
        auto [bl_low, bh_low]   = split_lohi(b_lo);
        auto [al_high, ah_high] = split_lohi(a_hi);
        auto [bl_high, bh_high] = split_lohi(b_hi);

        // 32-bit multiplications
        __m128i mul_low_low  = mul32x32<T>(al_low, bl_low);
        __m128i cross_low_1  = mul32x32<T>(al_low, bh_low);
        __m128i cross_low_2  = mul32x32<T>(ah_low, bl_low);
        __m128i mul_high_low = mul32x32<T>(al_high, bl_high);
        __m128i cross_high_1 = mul32x32<T>(al_high, bh_high);
        __m128i cross_high_2 = mul32x32<T>(ah_high, bl_high);

        // Combine cross terms
        __m128i cross_low_sum  = _mm_add_epi64(cross_low_1, cross_low_2);
        __m128i cross_high_sum = _mm_add_epi64(cross_high_1, cross_high_2);

        // Shift cross terms to align with bits 32–63
        __m128i cross_low_shifted  = _mm_slli_epi64(cross_low_sum, 32);
        __m128i cross_high_shifted = _mm_slli_epi64(cross_high_sum, 32);

        // Add to low-low product
        __m128i result_low  = _mm_add_epi64(mul_low_low, cross_low_shifted);
        __m128i result_high = _mm_add_epi64(mul_high_low, cross_high_shifted);

        // Combine results into 256-bit vector
        return _mm256_setr_m128i(result_low, result_high);
      }
      else { return slice_apply(eve::mul, a, b); }
    }
    else
    {
      // Handle the other cases
      return eve::mul(a, b);
    }
  }
  else if constexpr( c == category::int64x2 )
  {
    // If AVX-512; use its direct 64-bit multiplication instruction
    if constexpr( current_api >= eve::avx512 ) { return _mm_mullo_epi64(a, b); }
    else
    {
      // Split 64-bit integers into 32-bit low and high parts
      auto [a_low, a_high] = split_lohi(a);
      auto [b_low, b_high] = split_lohi(b);

      // 32-bit multiplications
      __m128i mul_low         = mul32x32<T>(a_low, b_low);  
      __m128i cross_mul_la_hb = mul32x32<T>(a_low, b_high); 
      __m128i cross_mul_lb_ha = mul32x32<T>(a_high, b_low); 

      // Combine cross terms and shift to align with bits 32–63
      __m128i cross_sum     = _mm_add_epi64(cross_mul_la_hb, cross_mul_lb_ha);
      __m128i cross_shifted = _mm_slli_epi64(cross_sum, 32);

      // Add low-low product and shifted cross terms
      return _mm_add_epi64(mul_low, cross_shifted);
    }
  }
  else if constexpr( c == category::uint64x8 ) return _mm512_mullo_epi64(a, b);
  else if constexpr( c == category::int32x16 ) return _mm512_mullo_epi32(a, b);
  else if constexpr( c == category::uint32x16 ) return _mm512_mullo_epi32(a, b);
  else if constexpr( ((c == category::int32x8) || (c == category::uint32x8))
                     && (current_api >= avx2) )
  {
    return _mm256_mullo_epi32(a, b);
  }
  else if constexpr( (c == category::int32x4) || (c == category::uint32x4) )
  {
    if constexpr( current_api >= sse4_1 ) { return _mm_mullo_epi32(a, b); }
    else
    {
      static constexpr auto half_size = ((N::value / 2) > 0) ? N::value / 2 : 1;
      using htype                     = wide<std::int64_t, fixed<half_size>>;

      htype mhi = _mm_setr_epi32(-1, 0, -1, 0);
      htype mlo = mhi;
      auto  la  = _mm_srli_si128(a, 4);
      auto  lb  = _mm_srli_si128(b, 4);

      mhi &= htype {_mm_mul_epu32(a, b)};
      mlo &= htype {_mm_mul_epu32(la, lb)};
      mhi |= htype {_mm_slli_si128(mlo, 4)};

      return mhi.storage();
    }
  }
  else if constexpr( (c == category::int16x16 || c == category::uint16x16) && current_api >= avx2 )
  {
    return _mm256_mullo_epi16(a, b);
  }
  else if constexpr( c == category::int16x32 ) return _mm512_mullo_epi16(a, b);
  else if constexpr( c == category::uint16x32 ) return _mm512_mullo_epi16(a, b);
  else if constexpr( c == category::int16x8 ) return _mm_mullo_epi16(a, b);
  else if constexpr( c == category::uint16x8 ) return _mm_mullo_epi16(a, b);
  else if constexpr( (c == category::int8x16) || (c == category::uint8x16) )
  {
    static constexpr auto half_size = ((N::value / 2) > 0) ? N::value / 2 : 1;

    using htype = wide<std::int16_t, fixed<half_size>>;

    htype mhi = _mm_set1_epi16(0x00FF);
    htype mlo = mhi;
    auto  la  = _mm_srli_epi16(a, 8);
    auto  lb  = _mm_srli_epi16(b, 8);

    mhi &= htype {_mm_mullo_epi16(a, b)};
    mlo &= htype {_mm_mullo_epi16(la, lb)};
    mhi |= htype {_mm_slli_epi16(mlo, 8)};

    return mhi.storage();
  }
  else
  {
    auto           s    = a;
    constexpr auto smul = [](auto va, auto vb) { return va * vb; };

    if constexpr( N::value >= 2 ) return slice_apply(smul, s, b);
    else return map(smul, s, b);
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
