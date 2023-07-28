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
namespace idx
{
  constexpr bool within_lane(std::span<const std::ptrdiff_t> idxs)
  {
    const std::ptrdiff_t ssize = std::ssize(idxs);
    const std::ptrdiff_t half  = ssize / 2;

    if( ssize % 2 ) return false;

    for( std::ptrdiff_t i = 0; i != half; ++i )
    {
      if( idxs[i] >= half ) return false;
    }

    for( std::ptrdiff_t i = half; i != ssize; ++i )
    {
      if( 0 <= idxs[i] && idxs[i] < half ) return false;
    }

    return true;
  }

} // namespace idx

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128_shifts_and_slides(pattern_t<I...> p, fixed<G> g, wide<T, N> x)
{
  constexpr std::array  idxs {I...};
  constexpr std::size_t reg_size = sizeof(T) * N::value;

  if constexpr( current_api == avx && reg_size == 32 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_element_bit_shift(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( constexpr auto slide = idxm::is_slide_left(idxs); slide )
  {
    constexpr int m = *slide * sizeof(T) * G;
    if constexpr( reg_size == 16 ) return _mm_bsrli_si128(x, m);
    else if constexpr( reg_size == 32 ) return _mm256_bsrli_epi128(x, m);
    else if constexpr( reg_size == 64 ) return _mm512_bsrli_epi128(x, m);
  }
  else if constexpr( constexpr auto slide = idxm::is_slide_right(idxs); slide )
  {
    constexpr int m = *slide * sizeof(T) * G;
    if constexpr( reg_size == 16 ) return _mm_bslli_si128(x, m);
    else if constexpr( reg_size == 32 ) return _mm256_bslli_epi128(x, m);
    else if constexpr( reg_size == 64 ) return _mm512_bslli_epi128(x, m);
  }
  else return no_matching_shuffle;
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128_4_shorts(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::size_t reg_size = sizeof(T) * N::value;

  if constexpr( sizeof(T) == 1 ) return no_matching_shuffle;
  else if constexpr ( current_api == avx && reg_size == 32 ) return no_matching_shuffle;
  else
  {
    constexpr auto idxs = idxm::reduce_repeated_pattern_until<8, I...>;
    if constexpr( idxs.size() > 8 || idxm::has_zeroes(idxs) ) return no_matching_shuffle;
    else
    {
      static_assert(G == 1);

      constexpr auto lohi = idxm::split_to_groups<4>(idxs);
      constexpr auto lo = lohi[0];
      constexpr auto hi = lohi[1];

      if constexpr( idxm::is_in_order_from(lo, 0) )
      {
        constexpr std::array hi_adjusted {hi[0] - 4, hi[1] - 4, hi[2] - 4, hi[3] - 4};
        constexpr int        m = idxm::x86_mm_shuffle_4(hi_adjusted);

        if constexpr( reg_size == 16 ) return _mm_shufflehi_epi16(x, m);
        else if constexpr( reg_size == 32 ) return _mm256_shufflehi_epi16(x, m);
        else if constexpr( reg_size == 64 ) return _mm512_shufflehi_epi16(x, m);
      }
      else if constexpr( idxm::is_in_order_from(hi, 4) )
      {
        constexpr int m = idxm::x86_mm_shuffle_4(lo);

        if constexpr( reg_size == 16 ) return _mm_shufflelo_epi16(x, m);
        else if constexpr( reg_size == 32 ) return _mm256_shufflelo_epi16(x, m);
        else if constexpr( reg_size == 64 ) return _mm512_shufflelo_epi16(x, m);
      }
      else return no_matching_shuffle;
    }
  }
}

/*
 * 16 byte shuffles that were duplicated in next arches between multiple lanes.
 */
template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_x86_within_128(pattern_t<I...> p, fixed<G> g, wide<T, N> x)
{
  constexpr std::array  idxs {I...};
  constexpr std::size_t reg_size = sizeof(T) * N::value;
  constexpr bool        zeroes   = idxm::has_zeroes(idxs);
  constexpr bool        avx_256  = current_api == avx && reg_size == 32;

  if constexpr( idxs.size() * G * sizeof(T) > 16 )
  {
    constexpr auto p_half = idxm::is_repeating_pattern(idxs);

    if constexpr( !p_half ) return no_matching_shuffle;
    else return shuffle_l2_x86_within_128(idxm::to_pattern<*p_half>(), g, x);
  }
  else if constexpr( auto r = shuffle_l2_x86_within_128_shifts_and_slides(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( sizeof(T) >= 4 && !zeroes )
  {
    constexpr int m = idxm::x86_mm_shuffle_4(idxs);

    if constexpr( reg_size == 16 ) return _mm_shuffle_epi32(x, m);
    else if constexpr( reg_size == 32 )
    {
      // _mm256_shuffle_epi32 has better throughput
      using f32x8 = eve::wide<float, eve::fixed<8>>;
      if constexpr( current_api >= avx2 ) return _mm256_shuffle_epi32(x, m);
      else return _mm256_permute_ps(eve::bit_cast(x, eve::as<f32x8> {}), m);
    }
    else if constexpr( reg_size == 64 ) return _mm512_shuffle_epi32(x, m);
  }
  else if constexpr( auto r = shuffle_l2_x86_within_128_4_shorts(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( constexpr auto rotation = idxm::is_rotate(idxs);
                     rotation && (current_api >= ssse3 && !avx_256) )
  {
    constexpr int m = 16 - G * sizeof(T) * *rotation;

    if constexpr( reg_size == 16 ) return _mm_alignr_epi8(x, x, m);
    else if constexpr( reg_size == 32 ) return _mm256_alignr_epi8(x, x, m);
    else if constexpr( reg_size == 64 ) return _mm512_alignr_epi8(x, x, m);
  }
  else return no_matching_shuffle;
}

// _mm_insert_epi
template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_x86_128_insert_one_zero(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs {I...};

  constexpr auto pos = eve::detail::idxm::is_just_setting_one_zero(idxs);
  if constexpr( !pos ) return no_matching_shuffle;
  else
  {
    static_assert(G == 1);

    if constexpr( sizeof(T) == 8 && *pos == 1 ) return _mm_move_epi64(x);
    else if constexpr( sizeof(T) == 2 ) return _mm_insert_epi16(x, 0, *pos);
    else if constexpr( current_api < sse4_1 ) return no_matching_shuffle;
    else if constexpr( sizeof(T) == 8 ) return _mm_insert_epi64(x, 0, *pos);
    else if constexpr( sizeof(T) == 4 ) return _mm_insert_epi32(x, 0, *pos);
    else return _mm_insert_epi8(x, 0, *pos);
  }
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sse2_), pattern_t<I...> p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_128_>
{
  constexpr std::array idxs {I...};

  if constexpr( idxs.size() * G != N::value ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_within_128(p, g, x); matched_shuffle<decltype(r)> )
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

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(avx_), pattern_t<I...> p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_256_> && (sizeof...(I) * G == N::value)
{
  constexpr std::array  idxs {I...};
  constexpr std::size_t gsize = sizeof(T) * G;

  if constexpr( idxs.size() * G != N::value ) return no_matching_shuffle;
  else if constexpr( matched_shuffle<decltype(shuffle_l2_x86_within_128(p, g, x))> )
  {
    return shuffle_l2_x86_within_128(p, g, x);
  }
  else if constexpr( current_api >= avx2 && gsize >= 8 && !idxm::has_zeroes(idxs) )
  {
    constexpr int shuffle = idxm::x86_mm_shuffle_4(idxs);
    return _mm256_permute4x64_epi64(x, shuffle);
  }
  else if constexpr( gsize == 16 )
  {
    constexpr int mm = idxm::x86_permute2f128_one_reg_mask(idxs);
    return _mm256_permute2f128_si256(x, x, mm);
  }
  else if constexpr( idx::within_lane(idxs) && gsize == 8 && !idxm::has_zeroes(idxs) )
  {
    using f64x4      = eve::wide<double, eve::fixed<4>>;
    constexpr int mm = idxm::x86_shuffle_4_in_lane(idxs);
    return _mm256_permute_pd(eve::bit_cast(x, eve::as<f64x4> {}), mm);
  }
  else return no_matching_shuffle;
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sse2_), pattern_t<I...>, fixed<G>, wide<T, N> x, wide<T, N> y)
requires std::same_as<abi_t<T, N>, x86_128_>
{
  constexpr std::array idxs {I...};

  if constexpr( idxs.size() * G != N::value ) return no_matching_shuffle;
  // Immediate blends are very good, even if are covered by other ops
  // https://stackoverflow.com/questions/76552874/how-should-i-chose-between-mm-move-sd-mm-shuffle-pd-mm-blend-pd
  //
  // FIX-1617 - enable `_mm_blend_epi16`
  else if constexpr( eve::current_api >= eve::sse4_1 && sizeof(T) >= 4
                     && idxm::is_blend(idxs, N::value / G) )
  {
    constexpr int m = idxm::x86_blend_immediate_mask(idxs);

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
    constexpr int m = _MM_SHUFFLE2(idxs[1] - 2, idxs[0]);
    return _mm_shuffle_pd(x_f64, y_f64, m);
  }
  else return no_matching_shuffle;
}
}
