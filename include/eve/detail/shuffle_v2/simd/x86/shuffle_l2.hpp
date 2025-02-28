//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/pragmas.hpp>

EVE_ALLOW_SHADOW_PRAGMA
namespace eve::detail
{

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_128_shifts_and_slides(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_element_bit_shift(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( constexpr auto slidel = idxm::is_slide_left(*P::repeated_16); slidel )
  {
    constexpr int m = *slidel * sizeof(T) * G;
    if constexpr( P::reg_size == 16 ) return _mm_bsrli_si128(x, m);
    else if constexpr( P::reg_size == 32 ) return _mm256_bsrli_epi128(x, m);
    else if constexpr( P::reg_size == 64 ) return _mm512_bsrli_epi128(x, m);
  }
  else if constexpr( constexpr auto slider = idxm::is_slide_right(*P::repeated_16); slider )
  {
    constexpr int m = *slider * sizeof(T) * G;
    if constexpr( P::reg_size == 16 ) return _mm_bslli_si128(x, m);
    else if constexpr( P::reg_size == 32 ) return _mm256_bslli_epi128(x, m);
    else if constexpr( P::reg_size == 64 ) return _mm512_bslli_epi128(x, m);
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_128_4_shorts(P, fixed<G>, wide<T, N> x)
{
  if constexpr( sizeof(T) == 1 ) return no_matching_shuffle;
  else if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
  else
  {
    if constexpr( P::has_zeroes ) return no_matching_shuffle;
    else
    {
      static_assert(G == 1);

      constexpr auto lohi = idxm::split_to_groups<4>(*P::repeated_16);
      constexpr auto lo   = lohi[0];
      constexpr auto hi   = lohi[1];

      if constexpr( idxm::is_in_order_from(lo, 0) )
      {
        constexpr std::array hi_adjusted {hi[0] - 4, hi[1] - 4, hi[2] - 4, hi[3] - 4};
        constexpr int        m = idxm::x86_mm_shuffle_4(hi_adjusted);

        if constexpr( P::reg_size == 16 ) return _mm_shufflehi_epi16(x, m);
        else if constexpr( P::reg_size == 32 ) return _mm256_shufflehi_epi16(x, m);
        else if constexpr( P::reg_size == 64 ) return _mm512_shufflehi_epi16(x, m);
      }
      else if constexpr( idxm::is_in_order_from(hi, 4) )
      {
        constexpr int m = idxm::x86_mm_shuffle_4(lo);

        if constexpr( P::reg_size == 16 ) return _mm_shufflelo_epi16(x, m);
        else if constexpr( P::reg_size == 32 ) return _mm256_shufflelo_epi16(x, m);
        else if constexpr( P::reg_size == 64 ) return _mm512_shufflelo_epi16(x, m);
      }
      else return no_matching_shuffle;
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_128_4x32(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( sizeof(T) * G < 4 ) return no_matching_shuffle;
  else if constexpr( !P::has_zeroes )
  {
    constexpr auto m = static_cast<_MM_PERM_ENUM>(idxm::x86_mm_shuffle_4(*P::repeated_16));

    if constexpr( P::reg_size == 16 ) return _mm_shuffle_epi32(x, m);
    else if constexpr( current_api == avx )
    {
      // Only do this on avx because _mm256_shuffle_epi32 has better throughput
      return _mm256_permute_ps(eve::bit_cast(x, eve::as<eve::wide<float>> {}), m);
    }
    else if constexpr( P::reg_size == 32 ) return _mm256_shuffle_epi32(x, m);
    else return _mm512_shuffle_epi32(x, m);
  }
  else if constexpr( current_api < avx512 ) return no_matching_shuffle;
  else
  {
    constexpr auto   m = static_cast<_MM_PERM_ENUM>(idxm::x86_mm_shuffle_4(*P::repeated_16));
    auto          mask = is_na_or_we_logical_mask(p, g, as(x)).storage();

    if constexpr( P::reg_size == 16 ) return _mm_maskz_shuffle_epi32(mask, x, m);
    else if constexpr( P::reg_size == 32 ) return _mm256_maskz_shuffle_epi32(mask, x, m);
    else return _mm512_maskz_shuffle_epi32(mask, x, m);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_128_alignr(P, fixed<G>, wide<T, N> x)
{
  if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
  else if constexpr( current_api < ssse3 ) return no_matching_shuffle;
  else
  {
    constexpr auto rotation = idxm::is_rotate(*P::repeated_16);

    if constexpr( !rotation ) return no_matching_shuffle;
    else
    {
      constexpr int m = 16 - G * sizeof(T) * *rotation;

      if constexpr( P::reg_size == 16 ) return _mm_alignr_epi8(x, x, m);
      else if constexpr( P::reg_size == 32 ) return _mm256_alignr_epi8(x, x, m);
      else return _mm512_alignr_epi8(x, x, m);
    }
  }
}

/*
 * 16 byte shuffles that were duplicated in next arches between multiple lanes.
 */
template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_128(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( !P::repeated_16 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_repeated_128_shifts_and_slides(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_repeated_128_4x32(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_repeated_128_4_shorts(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_repeated_128_alignr(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

// _mm_insert_epi
template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_128_insert_one_zero(P, fixed<G>, wide<T, N> x)
{
  constexpr auto pos = eve::detail::idxm::is_just_setting_one_zero(P::idxs);
  if constexpr( !pos ) return no_matching_shuffle;
  else if constexpr( P::reg_size == 16 )
  {
    constexpr int m = *pos;

    if constexpr( sizeof(T) == 8 && *pos == 1 ) return _mm_move_epi64(x);
    else if constexpr( sizeof(T) == 2 ) return _mm_insert_epi16(x, 0, m);
    else if constexpr( current_api < sse4_1 ) return no_matching_shuffle;
    else if constexpr( sizeof(T) == 8 ) return _mm_insert_epi64(x, 0, m);
    else if constexpr( sizeof(T) == 4 ) return _mm_insert_epi32(x, 0, m);
    else return _mm_insert_epi8(x, 0, m);
  }
  // avx versions seems to be sequence - better mask
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_256_permute4x64(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( P::g_size < 8 ) return no_matching_shuffle;
  else if constexpr( P::has_zeroes && current_api < avx512 ) return no_matching_shuffle;
  // Within lane is faster so prefer it
  else if constexpr( idxm::shuffle_within_halves(*P::repeated_32) )
  {
    constexpr int mm = idxm::x86_shuffle_4_in_lane(*P::repeated_32);

    auto x_f64 = bit_cast(x, eve::as<eve::wide<double, N>> {});

    if constexpr( !P::has_zeroes )
    {
      if constexpr( P::reg_size == 32 ) return _mm256_permute_pd(x_f64, mm);
      else return _mm512_permute_pd(x_f64, mm);
    }
    else
    {
      auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage();
      if constexpr( P::reg_size == 32 ) return _mm256_maskz_permute_pd(mask, x_f64, mm);
      else return _mm256_maskz_permute_pd(mask, x_f64, mm);
    }
  }
  else if constexpr( current_api > avx )
  {
    constexpr int mm = idxm::x86_mm_shuffle_4(*P::repeated_32);

    if constexpr( !P::has_zeroes )
    {
      if constexpr( P::reg_size == 32 ) return _mm256_permute4x64_epi64(x, mm);
      else return _mm512_permutex_epi64(x, mm);
    }
    else
    {
      auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage();

      if constexpr( P::reg_size == 32 ) return _mm256_maskz_permutex_epi64(mask, x, mm);
      else return _mm512_maskz_permutex_epi64(mask, x, mm);
    }
  }
  else return no_matching_shuffle;
}

/*
 * 32 byte shuffles that were duplicated in next arches between multiple lanes.
 */
template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_256(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( !P::repeated_32 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_repeated_256_permute4x64(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_u64x2(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( P::g_size < 16 ) return no_matching_shuffle;
  else if constexpr( P::reg_size == 32 )
  {
    constexpr int mm = idxm::x86_permute2f128_mask(P::idxs);
    return _mm256_permute2f128_si256(x, x, mm);
  }
  else
  {
    constexpr int mm = idxm::x86_mm_shuffle_4(P::idxs);

    if constexpr( !P::has_zeroes ) return _mm512_shuffle_i64x2(x, x, mm);
    else
    {
      auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage();
      return _mm512_maskz_shuffle_i64x2(mask, x, x, mm);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_alignr_epi32_self(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( P::g_size < 4 || current_api < avx512 ) return no_matching_shuffle;
  else if constexpr( constexpr auto rotation = idxm::is_rotate(P::idxs_no_na); !rotation )
  {
    return no_matching_shuffle;
  }
  else if constexpr( !P::has_zeroes )
  {
    static_assert(P::reg_size > 16, "sanity check - sse alignr is better");

    constexpr std::ptrdiff_t shift_epi32 = (N() - *rotation) * P::g_size / 4;
    constexpr std::ptrdiff_t shift_epi64 = (N() - *rotation) * P::g_size / 8;

    if constexpr( P::reg_size == 32 )
    {
      if constexpr( P::g_size >= 8 ) return _mm256_alignr_epi64(x, x, shift_epi64);
      else return _mm256_alignr_epi64(x, x, shift_epi32);
    }
    else
    {
      if constexpr( P::g_size >= 8 ) return _mm512_alignr_epi64(x, x, shift_epi64);
      else return _mm512_alignr_epi32(x, x, shift_epi32);
    }
  }
  else
  {
    constexpr std::ptrdiff_t shift_epi32 = (N() - *rotation) * P::g_size / 4;
    constexpr std::ptrdiff_t shift_epi64 = (N() - *rotation) * P::g_size / 8;

    auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage();

    if constexpr( P::reg_size == 16 )
    {
      if constexpr( P::g_size >= 8 ) return _mm128_maskz_alignr_epi64(mask, x, x, shift_epi64);
      else return _mm128_maskz_alignr_epi32(mask, x, x, shift_epi32);
    }
    else if constexpr( P::reg_size == 32 )
    {
      if constexpr( P::g_size >= 8 ) return _mm256_maskz_alignr_epi64(mask, x, x, shift_epi64);
      else return _mm256_maskz_alignr_epi32(mask, x, x, shift_epi32);
    }
    else
    {
      if constexpr( P::g_size >= 8 ) return _mm512_maskz_alignr_epi64(mask, x, x, shift_epi64);
      else return _mm512_maskz_alignr_epi32(mask, x, x, shift_epi32);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l2_x86_repeated_128(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_128_insert_one_zero(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_repeated_256(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_u64x2(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_alignr_epi32_self(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

// 2 register shuffles ---------------------------------------------------------

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_blend(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  // Immediate blends are very good, even if are covered by other ops
  // https://stackoverflow.com/questions/76552874/how-should-i-chose-between-mm-move-sd-mm-shuffle-pd-mm-blend-pd
  //

  // NOTE: no zeroing blend on avx512
  if constexpr( !idxm::is_blend(P::idxs, N::value / G) ) return no_matching_shuffle;
  else if constexpr( P::reg_size <= 32 && P::g_size >= 4 )
  {
    constexpr int m = idxm::x86_blend_immediate_mask(P::idxs, G);

    if constexpr( eve::current_api >= eve::sse4_1 && P::g_size >= 8 )
    {
      auto x_f64 = bit_cast(x, eve::as<eve::wide<double, N>> {});
      auto y_f64 = bit_cast(y, eve::as<eve::wide<double, N>> {});

      if constexpr( P::reg_size == 16 ) return _mm_blend_pd(x_f64, y_f64, m);
      else return _mm256_blend_pd(x_f64, y_f64, m);
    }
    else if constexpr( eve::current_api >= eve::sse4_1 && P::g_size >= 4 )
    {
      auto x_f32 = bit_cast(x, eve::as<eve::wide<float, N>> {});
      auto y_f32 = bit_cast(y, eve::as<eve::wide<float, N>> {});

      if constexpr( P::reg_size == 16 ) return _mm_blend_ps(x_f32, y_f32, m);
      else return _mm256_blend_ps(x_f32, y_f32, m);
    }
    // FIX-1617 - enable `_mm_blend_epi16`
    else return no_matching_shuffle;
  }
  else if constexpr( eve::current_api >= avx512 )
  {
    // On avx512 we don't count logical masks
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    return eve::if_else(m, y, x);
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_128x2_alignr(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
  else if constexpr( current_api < ssse3 ) return no_matching_shuffle;
  else
  {
    constexpr auto starts_from = idxm::is_slide_left_2(*P::repeated_16, P::reg_groups);

    if constexpr( !starts_from ) return no_matching_shuffle;
    else
    {
      constexpr std::ptrdiff_t shift = *starts_from * P::g_size;
      static_assert(shift < 16, "veryfing assumptions");
      // No support for maskz yet
      if constexpr( P::reg_size == 16 ) return _mm_alignr_epi8(y, x, shift);
      else if constexpr( P::reg_size == 32 ) return _mm256_alignr_epi8(y, x, shift);
      else return _mm512_alignr_epi8(y, x, shift);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_repeated_128x2(P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( !P::repeated_16 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_repeated_128x2_alignr(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128x2_shuffle_ps(P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( sizeof(T) < 4 ) return no_matching_shuffle;
  else if constexpr( P::has_zeroes && current_api < avx512 ) return no_matching_shuffle;
  else if constexpr( constexpr auto opt_mm = idxm::x86_shuffle_ps_2<P::g_size>(P::idxs); !opt_mm )
  {
    return no_matching_shuffle;
  }
  else
  {
    using floats_t = eve::wide<float, eve::fixed<N::value * sizeof(T) / sizeof(float)>>;
    auto x_f32     = bit_cast(x, eve::as<floats_t> {});
    auto y_f32     = bit_cast(y, eve::as<floats_t> {});

    constexpr int mm = *opt_mm;
    if constexpr( !P::has_zeroes )
    {
      if constexpr( P::reg_size == 16 ) return _mm_shuffle_ps(x_f32, y_f32, mm);
      else if constexpr( P::reg_size == 32 ) return _mm256_shuffle_ps(x_f32, y_f32, mm);
      else return _mm512_shuffle_ps(x_f32, y_f32, mm);
    }
    else
    {
      auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage();

      if constexpr( P::reg_size == 16 ) return _mm_maskz_shuffle_ps(mask, x_f32, y_f32, mm);
      else if constexpr( P::reg_size == 32 ) return _mm256_maskz_shuffle_ps(mask, x_f32, y_f32, mm);
      else return _mm512_maskz_shuffle_ps(mask, x_f32, y_f32, mm);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128x2(P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( !idxm::shuffle_within_n(P::idxs, 16 / sizeof(T)) )
  {
    return no_matching_shuffle;
  }
  else if constexpr( auto r = shuffle_l2_x86_within_128x2_shuffle_ps(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_permute2f128(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( P::g_size != 16 || P::reg_size != 32 ) return no_matching_shuffle;
  else
  {
    static_assert(!P::has_zeroes, "sanity check, no 0s/we or it's not two register");
    constexpr int m = idxm::x86_permute2f128_mask(P::idxs);
    return _mm256_permute2f128_si256(x, y, m);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_shuffle_i32x4(P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  // the _mm256_maskz_shuffle_i32x4 is not supported yet.
  if constexpr( sizeof(T) < 4 || P::reg_size < 64 ) return no_matching_shuffle;
  else if constexpr( constexpr auto m = idxm::mm512_shuffle_i64x2_idx(P::idxs_no_na); !m )
  {
    return no_matching_shuffle;
  }
  else
  {
    constexpr int mm = *m;
    if constexpr( !P::has_zeroes ) return _mm512_shuffle_i64x2(x, y, mm);
    else
    {
      auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage();
      if constexpr( sizeof(T) >= 8 ) return _mm512_maskz_shuffle_i64x2(mask, x, y, mm);
      else return _mm512_maskz_shuffle_i64x2(mask, x, y, mm);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_shuffle_128_2regs(P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( auto r = shuffle_l2_x86_permute2f128(p, g, x, y); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_shuffle_i32x4(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_alignr_epi32(P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( P::g_size < 4 ) return no_matching_shuffle;
  else if constexpr( current_api < avx512 ) return no_matching_shuffle;
  else if constexpr( constexpr auto starts_from = idxm::is_in_order(P::idxs_no_na); !starts_from )
  {
    return no_matching_shuffle;
  }
  else if constexpr( !P::has_zeroes )
  {
    static_assert(P::reg_size > 16, "sanity check - sse alignr is better");

    constexpr std::ptrdiff_t shift_epi32 = *starts_from * P::g_size / 4;
    constexpr std::ptrdiff_t shift_epi64 = *starts_from * P::g_size / 8;

    if constexpr( P::reg_size == 32 )
    {
      if constexpr( P::g_size >= 8 ) return _mm256_alignr_epi64(y, x, shift_epi64);
      else return _mm256_alignr_epi64(y, x, shift_epi32);
    }
    else
    {
      if constexpr( P::g_size >= 8 ) return _mm512_alignr_epi64(y, x, shift_epi64);
      else return _mm512_alignr_epi32(y, x, shift_epi32);
    }
  }
  else
  {
    constexpr std::ptrdiff_t shift_epi32 = *starts_from * P::g_size / 4;
    constexpr std::ptrdiff_t shift_epi64 = *starts_from * P::g_size / 8;

    auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage();

    if constexpr( P::reg_size == 16 )
    {
      if constexpr( P::g_size >= 8 ) return _mm128_maskz_alignr_epi64(mask, y, x, shift_epi64);
      else return _mm128_maskz_alignr_epi32(mask, y, x, shift_epi32);
    }
    else if constexpr( P::reg_size == 32 )
    {
      if constexpr( P::g_size >= 8 ) return _mm256_maskz_alignr_epi64(mask, y, x, shift_epi64);
      else return _mm256_maskz_alignr_epi32(mask, y, x, shift_epi32);
    }
    else
    {
      if constexpr( P::g_size >= 8 ) return _mm512_maskz_alignr_epi64(mask, y, x, shift_epi64);
      else return _mm512_maskz_alignr_epi32(mask, y, x, shift_epi32);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l2_x86_blend(p, g, x, y); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_repeated_128x2(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_within_128x2(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_shuffle_128_2regs(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_alignr_epi32(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}
}

EVE_RESTORE_ALLOW_SHADOW_PRAGMA
