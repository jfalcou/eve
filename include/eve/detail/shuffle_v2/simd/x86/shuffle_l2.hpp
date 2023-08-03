//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::detail
{

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128_shifts_and_slides(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_element_bit_shift(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( constexpr auto slide = idxm::is_slide_left(*P::repeated_16); slide )
  {
    constexpr int m = *slide * sizeof(T) * G;
    if constexpr( P::reg_size == 16 ) return _mm_bsrli_si128(x, m);
    else if constexpr( P::reg_size == 32 ) return _mm256_bsrli_epi128(x, m);
    else if constexpr( P::reg_size == 64 ) return _mm512_bsrli_epi128(x, m);
  }
  else if constexpr( constexpr auto slide = idxm::is_slide_right(*P::repeated_16); slide )
  {
    constexpr int m = *slide * sizeof(T) * G;
    if constexpr( P::reg_size == 16 ) return _mm_bslli_si128(x, m);
    else if constexpr( P::reg_size == 32 ) return _mm256_bslli_epi128(x, m);
    else if constexpr( P::reg_size == 64 ) return _mm512_bslli_epi128(x, m);
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128_4_shorts(P, fixed<G>, wide<T, N> x)
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
shuffle_l2_x86_within_128_4x32(P, fixed<G>, wide<T, N> x)
{
  if constexpr( sizeof(T) * G < 4 || P::has_zeroes ) return no_matching_shuffle;
  else
  {
    constexpr int m = idxm::x86_mm_shuffle_4(*P::repeated_16);

    if constexpr( P::reg_size == 16 ) return _mm_shuffle_epi32(x, m);
    else if constexpr( current_api == avx )
    {
      // Only do this on avx because _mm256_shuffle_epi32 has better throughput
      return _mm256_permute_ps(eve::bit_cast(x, eve::as<eve::wide<float>> {}), m);
    }
    else if constexpr( P::reg_size == 32 ) return _mm256_shuffle_epi32(x, m);
    else return _mm512_shuffle_epi32(x, m);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128_alignr(P, fixed<G>, wide<T, N> x)
{
  if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
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
shuffle_l2_x86_within_128(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( !P::repeated_16 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_within_128_shifts_and_slides(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_within_128_4x32(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_within_128_4_shorts(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_within_128_alignr(p, g, x);
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
  constexpr auto pos = eve::detail::idxm::is_just_setting_one_zero(P::idxs2match);
  if constexpr( !pos ) return no_matching_shuffle;
  else if constexpr ( P::reg_size == 16 )
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
shuffle_l2_x86_within_256_permute4x64(P, fixed<G>, wide<T, N> x)
{
  if constexpr( P::g_size < 8 || P::has_zeroes ) return no_matching_shuffle;
  // Within lane is faster so prefer it
  else if constexpr( idxm::shuffle_within_halves(*P::repeated_32) )
  {
    constexpr int mm = idxm::x86_shuffle_4_in_lane(*P::repeated_32);

    auto x_f64 = bit_cast(x, eve::as<eve::wide<double, N>> {});

    if constexpr( P::reg_size == 32 ) return _mm256_permute_pd(x_f64, mm);
    else return _mm512_permute_pd(x_f64, mm);
  }
  else if constexpr( current_api > avx )
  {
    constexpr int mm = idxm::x86_mm_shuffle_4(*P::repeated_32);

    if constexpr( P::reg_size == 32 ) return _mm256_permute4x64_epi64(x, mm);
    else return _mm512_permutex_epi64(x, mm);
  }
  else return no_matching_shuffle;
}

/*
 * 32 byte shuffles that were duplicated in next arches between multiple lanes.
 */
template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_256(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( !P::repeated_32 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_within_256_permute4x64(p, g, x);
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
  else if constexpr ( P::reg_size == 32)
  {
    constexpr int mm = idxm::x86_permute2f128_one_reg_mask(P::idxs);
    return _mm256_permute2f128_si256(x, x, mm);
  }
  else
  {
    constexpr int mm = idxm::x86_mm_shuffle_4(P::idxs);

    if constexpr( !P::has_zeroes ) return _mm512_shuffle_i64x2(x, x, mm);
    else
    {
      // avx512 masks don't count
      return _mm512_maskz_shuffle_i64x2(
          is_na_or_we_mask(p, g, eve::as<logical<wide<T, N>>> {}).storage(), x, x, mm);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_128_> && (P::out_reg_size == 16)
{
  if constexpr( auto r = shuffle_l2_x86_within_128(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_128_insert_one_zero(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}


template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(avx_), P p, fixed<G> g, wide<T, N> x)
requires (P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l2_x86_within_128(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_128_insert_one_zero(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_within_256(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_u64x2(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sse2_), P, fixed<G>, wide<T, N> x, wide<T, N> y)
requires std::same_as<abi_t<T, N>, x86_128_> && (P::out_reg_size == P::reg_size)
{
  // Immediate blends are very good, even if are covered by other ops
  // https://stackoverflow.com/questions/76552874/how-should-i-chose-between-mm-move-sd-mm-shuffle-pd-mm-blend-pd
  //
  // FIX-1617 - enable `_mm_blend_epi16`
  if constexpr( eve::current_api >= eve::sse4_1 && sizeof(T) >= 4
                && idxm::is_blend(P::idxs2match, N::value / G) )
  {
    constexpr int m = idxm::x86_blend_immediate_mask(P::idxs2match);

    if constexpr( sizeof(T) == 8 )
    {
      auto x_f64 = bit_cast(x, eve::as<eve::wide<double, eve::fixed<2>>> {});
      auto y_f64 = bit_cast(y, eve::as<eve::wide<double, eve::fixed<2>>> {});
      return _mm_blend_pd(x_f64, y_f64, m);
    }
    else if constexpr( sizeof(T) == 4 )
    {
      auto x_f32 = bit_cast(x, eve::as<eve::wide<float, eve::fixed<4>>> {});
      auto y_f32 = bit_cast(y, eve::as<eve::wide<float, eve::fixed<4>>> {});
      return _mm_blend_ps(x_f32, y_f32, m);
    }
#if 0 // FIX-1617 - enable `_mm_blend_epi16`
    else
    {
      //
      return _mm_blend_epi16(x, y, m);
    }
#endif
  }
  else if constexpr( sizeof(T) == 8 )
  {
    // half from x, half from y
    // No w/e or zeroes are possible here
    auto x_f64 = bit_cast(x, eve::as<eve::wide<double, eve::fixed<2>>> {});
    auto y_f64 = bit_cast(y, eve::as<eve::wide<double, eve::fixed<2>>> {});

    // There is also _mm_move_sd but there is no reason to generate it for us.
    // Compiler sometimes transforms.
    constexpr int m = _MM_SHUFFLE2(P::idxs2match[1] - 2, P::idxs2match[0]);
    return _mm_shuffle_pd(x_f64, y_f64, m);
  }
  else return no_matching_shuffle;
}
}
