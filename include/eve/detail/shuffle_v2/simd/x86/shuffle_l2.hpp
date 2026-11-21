//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>

EVE_NAMESPACE::_
{

template<std::ptrdiff_t g_size, bool hi, arithmetic_scalar_value T, width_type N>
 auto
x86_unpack(wide<T, N> x, wide<T, N> y)
{
  constexpr std::ptrdiff_t reg_size = sizeof(T) * wide<T, N>::size();

  if constexpr( reg_size == 16 )
  {
    if constexpr( g_size == 1 ) return hi ? _mm_unpackhi_epi8(x, y) : _mm_unpacklo_epi8(x, y);
    else if constexpr( g_size == 2 ) return hi ? _mm_unpackhi_epi16(x, y) : _mm_unpacklo_epi16(x, y);
    else if constexpr( g_size == 4 ) return hi ? _mm_unpackhi_epi32(x, y) : _mm_unpacklo_epi32(x, y);
    else return hi ? _mm_unpackhi_epi64(x, y) : _mm_unpacklo_epi64(x, y);
  }
  else if constexpr( reg_size == 32 && current_api == avx )
  {
    // avx only has floating point unpacks
    static_assert(g_size >= 4, "verifying assumptions");

    if constexpr( g_size == 4 )
    {
      using f32 = wide<float, 8>;
      auto xf   = bit_cast(x, as<f32> {});
      auto yf   = bit_cast(y, as<f32> {});
      return hi ? _mm256_unpackhi_ps(xf, yf) : _mm256_unpacklo_ps(xf, yf);
    }
    else
    {
      using f64 = wide<double, 4>;
      auto xf   = bit_cast(x, as<f64> {});
      auto yf   = bit_cast(y, as<f64> {});
      return hi ? _mm256_unpackhi_pd(xf, yf) : _mm256_unpacklo_pd(xf, yf);
    }
  }
  else if constexpr( reg_size == 32 )
  {
    if constexpr( g_size == 1 ) return hi ? _mm256_unpackhi_epi8(x, y) : _mm256_unpacklo_epi8(x, y);
    else if constexpr( g_size == 2 )
      return hi ? _mm256_unpackhi_epi16(x, y) : _mm256_unpacklo_epi16(x, y);
    else if constexpr( g_size == 4 )
      return hi ? _mm256_unpackhi_epi32(x, y) : _mm256_unpacklo_epi32(x, y);
    else return hi ? _mm256_unpackhi_epi64(x, y) : _mm256_unpacklo_epi64(x, y);
  }
  else
  {
    if constexpr( g_size == 1 ) return hi ? _mm512_unpackhi_epi8(x, y) : _mm512_unpacklo_epi8(x, y);
    else if constexpr( g_size == 2 )
      return hi ? _mm512_unpackhi_epi16(x, y) : _mm512_unpacklo_epi16(x, y);
    else if constexpr( g_size == 4 )
      return hi ? _mm512_unpackhi_epi32(x, y) : _mm512_unpacklo_epi32(x, y);
    else return hi ? _mm512_unpackhi_epi64(x, y) : _mm512_unpacklo_epi64(x, y);
  }
}

// Low 16 bytes of a register.
template<arithmetic_scalar_value T, width_type N>
 __m128i
x86_low_128(wide<T, N> x)
{
  constexpr std::ptrdiff_t reg_size = sizeof(T) * wide<T, N>::size();
  if constexpr( reg_size == 16 ) return x;
  else if constexpr( reg_size == 32 ) return _mm256_castsi256_si128(x);
  else return _mm512_castsi512_si128(x);
}

// Low 16 bytes of `lo` + low 16 bytes of `hi`
template<arithmetic_scalar_value T, width_type N>
 auto
x86_insert_hi_128(wide<T, N> lo, wide<T, N> hi)
{
  if constexpr( current_api == avx ) return _mm256_insertf128_si256(lo, x86_low_128(hi), 1);
  else return _mm256_inserti128_si256(lo, x86_low_128(hi), 1);
}

template<std::ptrdiff_t reg_size, std::ptrdiff_t from, std::ptrdiff_t to>
 auto
x86_cvtepu(auto src)
{
  if constexpr( reg_size == 16 )
  {
    if constexpr( from == 1 && to == 2 ) return _mm_cvtepu8_epi16(src);
    else if constexpr( from == 1 && to == 4 ) return _mm_cvtepu8_epi32(src);
    else if constexpr( from == 1 && to == 8 ) return _mm_cvtepu8_epi64(src);
    else if constexpr( from == 2 && to == 4 ) return _mm_cvtepu16_epi32(src);
    else if constexpr( from == 2 && to == 8 ) return _mm_cvtepu16_epi64(src);
    else return _mm_cvtepu32_epi64(src);
  }
  else if constexpr( reg_size == 32 )
  {
    if constexpr( from == 1 && to == 2 ) return _mm256_cvtepu8_epi16(src);
    else if constexpr( from == 1 && to == 4 ) return _mm256_cvtepu8_epi32(src);
    else if constexpr( from == 1 && to == 8 ) return _mm256_cvtepu8_epi64(src);
    else if constexpr( from == 2 && to == 4 ) return _mm256_cvtepu16_epi32(src);
    else if constexpr( from == 2 && to == 8 ) return _mm256_cvtepu16_epi64(src);
    else return _mm256_cvtepu32_epi64(src);
  }
  else
  {
    if constexpr( from == 1 && to == 2 ) return _mm512_cvtepu8_epi16(src);
    else if constexpr( from == 1 && to == 4 ) return _mm512_cvtepu8_epi32(src);
    else if constexpr( from == 1 && to == 8 ) return _mm512_cvtepu8_epi64(src);
    else if constexpr( from == 2 && to == 4 ) return _mm512_cvtepu16_epi32(src);
    else if constexpr( from == 2 && to == 8 ) return _mm512_cvtepu16_epi64(src);
    else return _mm512_cvtepu32_epi64(src);
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128_shifts_and_slides(P p, lanes_t<G> g, wide<T, N> x)
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

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128_4_shorts(P, lanes_t<G>, wide<T, N> x)
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

      // shufflelo/shufflehi can't move elements between the halves
      constexpr auto within = [](auto half, std::ptrdiff_t from)
      {
        for( auto i : half )
        {
          if( i != we_ && (i < from || i >= from + 4) ) return false;
        }
        return true;
      };

      constexpr auto minus_4 = [](std::ptrdiff_t i) { return i == we_ ? we_ : i - 4; };

      if constexpr( idxm::is_in_order_from(lo, 0) && within(hi, 4) )
      {
        constexpr std::array hi_adjusted {
            minus_4(hi[0]), minus_4(hi[1]), minus_4(hi[2]), minus_4(hi[3])};
        constexpr int        m = idxm::x86_mm_shuffle_4(hi_adjusted);

        if constexpr( P::reg_size == 16 ) return _mm_shufflehi_epi16(x, m);
        else if constexpr( P::reg_size == 32 ) return _mm256_shufflehi_epi16(x, m);
        else if constexpr( P::reg_size == 64 ) return _mm512_shufflehi_epi16(x, m);
      }
      else if constexpr( idxm::is_in_order_from(hi, 4) && within(lo, 0) )
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

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128_4x32(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( sizeof(T) * G < 4 || P::has_zeroes ) return no_matching_shuffle;
  else
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
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128_alignr(P, lanes_t<G>, wide<T, N> x)
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

// _mm_unpacklo_epi8(x, x) and friends.
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128_unpack_self(P, lanes_t<G>, wide<T, N> x)
{
  // 4 and 8 byte elements are covered by _mm_shuffle_epi32
  if constexpr( P::g_size > 2 || P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( P::reg_size == 32 && current_api < avx2 ) return no_matching_shuffle;
  else if constexpr( constexpr auto hi = idxm::x86_is_unpack(*P::repeated_16, 0); !hi )
  {
    return no_matching_shuffle;
  }
  else return x86_unpack<P::g_size, *hi>(x, x);
}

/*
 * 16 byte shuffles that were duplicated in next arches between multiple lanes.
 */
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128(P p, lanes_t<G> g, wide<T, N> x)
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
  else if constexpr( auto r = shuffle_l2_x86_repeated_128_unpack_self(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

// _mm_insert_epi
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_128_insert_one_zero(P, lanes_t<G>, wide<T, N> x)
{
  constexpr auto pos = eve::_::idxm::is_just_setting_one_zero(P::idxs);
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

// _mm_cvtepu8_epi16 and friends
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_zero_extend(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( current_api < sse4_1 || P::g_size > 4 ) return no_matching_shuffle;
  else if constexpr( P::reg_size == 32 && current_api < avx2 ) return no_matching_shuffle;
  else if constexpr( constexpr auto ratio = idxm::x86_is_zero_extend(P::idxs, 8 / P::g_size);
                     !ratio )
  {
    return no_matching_shuffle;
  }
  else
  {
    constexpr std::ptrdiff_t from = P::g_size;
    constexpr std::ptrdiff_t to   = P::g_size * *ratio;

    // zmm from ymm is the only case that needs more than 16 bytes
    if constexpr( P::reg_size == 64 && *ratio == 2 )
    {
      return x86_cvtepu<P::reg_size, from, to>(_mm512_castsi512_si256(x));
    }
    else return x86_cvtepu<P::reg_size, from, to>(x86_low_128(x));
  }
}

// _mm_broadcastb_epi8 and friends.
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_broadcast_0(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( current_api < avx2 || P::g_size > 8 || P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( constexpr auto lane = idxm::is_lane_broadcast(P::idxs); !lane || *lane != 0 )
  {
    return no_matching_shuffle;
  }
  else
  {
    __m128i lo = x86_low_128(x);

    if constexpr( P::reg_size == 16 )
    {
      if constexpr( P::g_size == 1 ) return _mm_broadcastb_epi8(lo);
      else if constexpr( P::g_size == 2 ) return _mm_broadcastw_epi16(lo);
      else if constexpr( P::g_size == 4 ) return _mm_broadcastd_epi32(lo);
      else return _mm_broadcastq_epi64(lo);
    }
    else if constexpr( P::reg_size == 32 )
    {
      if constexpr( P::g_size == 1 ) return _mm256_broadcastb_epi8(lo);
      else if constexpr( P::g_size == 2 ) return _mm256_broadcastw_epi16(lo);
      else if constexpr( P::g_size == 4 ) return _mm256_broadcastd_epi32(lo);
      else return _mm256_broadcastq_epi64(lo);
    }
    else
    {
      if constexpr( P::g_size == 1 ) return _mm512_broadcastb_epi8(lo);
      else if constexpr( P::g_size == 2 ) return _mm512_broadcastw_epi16(lo);
      else if constexpr( P::g_size == 4 ) return _mm512_broadcastd_epi32(lo);
      else return _mm512_broadcastq_epi64(lo);
    }
  }
}

// _mm_insert_ps(x, x): zero any subset + move one element.
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_insert_ps_self(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( current_api < sse4_1 || P::reg_size != 16 || P::g_size != 4 )
  {
    return no_matching_shuffle;
  }
  else if constexpr( constexpr auto imm = idxm::x86_insert_ps_imm(P::idxs, 0, 0); !imm )
  {
    return no_matching_shuffle;
  }
  else
  {
    auto xf = bit_cast(x, as<wide<float, 4>> {});
    return _mm_insert_ps(xf, xf, *imm);
  }
}

// _mm_rol_epi32 / _mm_rol_epi64: rotating smaller elements within 4 or 8 bytes.
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_rotate_within_element(P, lanes_t<G>, wide<T, N> x)
{
  constexpr std::ptrdiff_t element = P::g_size * std::ssize(P::most_repeated);

  if constexpr( current_api < avx512 || P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( element != 4 && element != 8 ) return no_matching_shuffle;
  else if constexpr( constexpr auto r = idxm::is_rotate(P::most_repeated); !r || *r == 0 )
  {
    return no_matching_shuffle;
  }
  else
  {
    constexpr int bits = *r * P::g_size * 8;

    if constexpr( element == 4 )
    {
      if constexpr( P::reg_size == 16 ) return _mm_rol_epi32(x, bits);
      else if constexpr( P::reg_size == 32 ) return _mm256_rol_epi32(x, bits);
      else return _mm512_rol_epi32(x, bits);
    }
    else
    {
      if constexpr( P::reg_size == 16 ) return _mm_rol_epi64(x, bits);
      else if constexpr( P::reg_size == 32 ) return _mm256_rol_epi64(x, bits);
      else return _mm512_rol_epi64(x, bits);
    }
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_independent_permute2x64(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( P::g_size != 8 || P::reg_size < 32 ) return no_matching_shuffle;
  else if constexpr( P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( !idxm::shuffle_within_n(P::idxs, 2) ) return no_matching_shuffle;
  else
  {
    constexpr int mm = idxm::x86_permute_pd(P::idxs);

    auto x_f64 = bit_cast(x, eve::as<eve::wide<double, N>> {});

    if constexpr( P::reg_size == 32 ) return _mm256_permute_pd(x_f64, mm);
    else return _mm512_permute_pd(x_f64, mm);
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_256_permute4x64(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( P::g_size != 8 || eve::current_api < avx2 ) return no_matching_shuffle;
  else if constexpr( P::has_zeroes ) return no_matching_shuffle;
  else
  {
    constexpr int mm = idxm::x86_mm_shuffle_4(*P::repeated_32);

    if constexpr( P::reg_size == 32 ) return _mm256_permute4x64_epi64(x, mm);
    else return _mm512_permutex_epi64(x, mm);
  }
}

/*
 * 32 byte shuffles that were duplicated in next arches between multiple lanes.
 */
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_256(P p, lanes_t<G> g, wide<T, N> x)
{
  if constexpr( !P::repeated_32 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_repeated_256_permute4x64(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_u64x2(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( P::g_size < 16 ) return no_matching_shuffle;
  else if constexpr( P::reg_size == 32 && P::idxs[0] == 0 && P::idxs[1] == 0 )
  {
    return x86_insert_hi_128(x, x);
  }
  else if constexpr( P::reg_size == 32 )
  {
    constexpr int mm = idxm::x86_permute2f128_mask(P::idxs);
    return _mm256_permute2f128_si256(x, x, mm);
  }
  else
  {
    constexpr int mm = idxm::x86_mm_shuffle_4(P::idxs);

    return _mm512_shuffle_i64x2(x, x, mm);
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_alignr_epi32_self(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( P::g_size < 4 || current_api < avx512 || P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( constexpr auto rotation = idxm::is_rotate(P::idxs_no_na); !rotation )
  {
    return no_matching_shuffle;
  }
  else
  {
    static_assert(P::reg_size > 16, "sanity check - sse alignr is better");

    constexpr std::ptrdiff_t shift_epi32 = (N - *rotation) * P::g_size / 4;
    constexpr std::ptrdiff_t shift_epi64 = (N - *rotation) * P::g_size / 8;

    if constexpr( P::reg_size == 32 )
    {
      static_assert(P::g_size != 8, "_mm256_permute4x64_epi64 should cover this");
      return _mm256_alignr_epi32(x, x, shift_epi32);
    }
    else
    {
      if constexpr( P::g_size >= 8 ) return _mm512_alignr_epi64(x, x, shift_epi64);
      else return _mm512_alignr_epi32(x, x, shift_epi32);
    }
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_(EVE_SUPPORTS(sse2_), P p, lanes_t<G> g, wide<T, N> x)
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
  else if constexpr( auto r = shuffle_l2_x86_zero_extend(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_insert_ps_self(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_rotate_within_element(p, g, x);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_independent_permute2x64(p, g, x);
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
  else if constexpr( auto r = shuffle_l2_x86_broadcast_0(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

// smaller output -------------------------------------------------------------

// _mm256_extracti128_si256 and friends: a 16/32 byte part, that is not the lowest one.
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_extract(P, lanes_t<G>, wide<T, N> x)
{
  constexpr auto start = idxm::is_in_order(P::idxs);

  if constexpr( !start || *start <= 0 ) return no_matching_shuffle;
  else if constexpr( P::out_reg_size < 16 || (*start * P::g_size) % P::out_reg_size )
  {
    return no_matching_shuffle;
  }
  else
  {
    constexpr int part = *start * P::g_size / P::out_reg_size;

    if constexpr( P::reg_size == 32 )
    {
      if constexpr( current_api == avx ) return _mm256_extractf128_si256(x, part);
      else return _mm256_extracti128_si256(x, part);
    }
    else if constexpr( P::out_reg_size == 32 ) return _mm512_extracti64x4_epi64(x, part);
    else return _mm512_extracti32x4_epi32(x, part);
  }
}

template<std::ptrdiff_t reg_size, std::ptrdiff_t from, std::ptrdiff_t to>
 auto
x86_cvtepi_truncate(auto x)
{
#define EVE_X86_TRUNCATE(F, T)                                                                     \
  if constexpr( reg_size == 16 ) return _mm_cvtepi##F##_epi##T(x);                                 \
  else if constexpr( reg_size == 32 ) return _mm256_cvtepi##F##_epi##T(x);                         \
  else return _mm512_cvtepi##F##_epi##T(x)

  if constexpr( from == 2 ) { EVE_X86_TRUNCATE(16, 8); }
  else if constexpr( from == 4 && to == 1 ) { EVE_X86_TRUNCATE(32, 8); }
  else if constexpr( from == 4 ) { EVE_X86_TRUNCATE(32, 16); }
  else if constexpr( to == 1 ) { EVE_X86_TRUNCATE(64, 8); }
  else if constexpr( to == 2 ) { EVE_X86_TRUNCATE(64, 16); }
  else { EVE_X86_TRUNCATE(64, 32); }

#undef EVE_X86_TRUNCATE
}

// _mm_cvtepi64_epi32 and friends (avx512)
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_truncate(P, lanes_t<G>, wide<T, N> x)
{
  if constexpr( current_api < avx512 || P::g_size > 4 ) return no_matching_shuffle;
  else if constexpr( constexpr auto ratio = idxm::x86_is_truncation(P::idxs, P::reg_groups);
                     !ratio || P::g_size * *ratio > 8 )
  {
    return no_matching_shuffle;
  }
  else return x86_cvtepi_truncate<P::reg_size, P::g_size * *ratio, P::g_size>(x);
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_(EVE_SUPPORTS(sse2_), P p, lanes_t<G> g, wide<T, N> x)
requires(P::out_reg_size < P::reg_size)
{
  if constexpr( auto r = shuffle_l2_x86_extract(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_truncate(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

// 2 register shuffles ---------------------------------------------------------

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_blend(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  // Immediate blends are very good, even if are covered by other ops
  // https://stackoverflow.com/questions/76552874/how-should-i-chose-between-mm-move-sd-mm-shuffle-pd-mm-blend-pd
  //

  // NOTE: no zeroing blend on avx512
  if constexpr( !idxm::is_blend(P::idxs, N / G) ) return no_matching_shuffle;
  else if constexpr( P::reg_size <= 32 && P::g_size >= 4 )
  {
    constexpr int m = idxm::x86_blend_immediate_mask(P::idxs, G);

    if constexpr( eve::current_api >= eve::avx2 )
    {
      // integer blend, no int/float domain crossing
      constexpr int m32 = idxm::x86_blend_epi32_mask(P::idxs, P::reg_groups, P::g_size / 4);

      if constexpr( P::reg_size == 16 ) return _mm_blend_epi32(x, y, m32);
      else return _mm256_blend_epi32(x, y, m32);
    }
    else if constexpr( eve::current_api >= eve::sse4_1 && P::g_size >= 8 )
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
    else return no_matching_shuffle;
  }
  else if constexpr( P::g_size == 2 && current_api >= sse4_1 && current_api < avx512
                     && P::reg_size == 16 )
  {
    constexpr int m = idxm::x86_blend_epi16_mask(P::idxs, P::reg_groups);
    return _mm_blend_epi16(x, y, m);
  }
  else if constexpr( P::g_size == 2 && current_api >= avx2 && current_api < avx512
                     && P::reg_size == 32 )
  {
    // the immediate is shared between the 16 byte lanes
    if constexpr( !P::repeated_16 ) return no_matching_shuffle;
    else
    {
      constexpr int m = idxm::x86_blend_epi16_mask(*P::repeated_16, P::reg_groups);
      return _mm256_blend_epi16(x, y, m);
    }
  }
  else if constexpr( eve::current_api >= avx512 )
  {
    // On avx512 we don't count logical masks
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    return eve::if_else(m, y, x);
  }
  else return no_matching_shuffle;
}

// _mm_insert_ps(x, y) / _mm_insert_ps(y, x): one element from the other register + zeroing.
template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_insert_ps(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( current_api < sse4_1 || P::reg_size != 16 || P::g_size != 4 )
  {
    return no_matching_shuffle;
  }
  else
  {
    constexpr auto x_base = idxm::x86_insert_ps_imm(P::idxs, 0, 4);
    constexpr auto y_base = idxm::x86_insert_ps_imm(P::idxs, 4, 0);

    auto xf = bit_cast(x, as<wide<float, 4>> {});
    auto yf = bit_cast(y, as<wide<float, 4>> {});

    if constexpr( x_base ) return _mm_insert_ps(xf, yf, *x_base);
    else if constexpr( y_base ) return _mm_insert_ps(yf, xf, *y_base);
    else return no_matching_shuffle;
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128x2_alignr(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
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

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128x2_shuffle_ps(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( sizeof(T) < 4 || P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( constexpr auto opt_mm = idxm::x86_shuffle_ps_2<P::g_size>(*P::repeated_16, P::reg_groups); !opt_mm )
  {
    return no_matching_shuffle;
  }
  else
  {
    using floats_t = eve::wide<float, N * sizeof(T) / sizeof(float)>;
    auto x_f32     = bit_cast(x, eve::as<floats_t> {});
    auto y_f32     = bit_cast(y, eve::as<floats_t> {});

    constexpr int mm = *opt_mm;
    if constexpr( P::reg_size == 16 ) return _mm_shuffle_ps(x_f32, y_f32, mm);
    else if constexpr( P::reg_size == 32 ) return _mm256_shuffle_ps(x_f32, y_f32, mm);
    else return _mm512_shuffle_ps(x_f32, y_f32, mm);
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128x2_unpack(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( P::g_size > 8 || P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( P::reg_size == 32 && current_api == avx && P::g_size < 4 )
  {
    return no_matching_shuffle;
  }
  else if constexpr( constexpr auto hi = idxm::x86_is_unpack(*P::repeated_16, P::reg_groups); !hi )
  {
    return no_matching_shuffle;
  }
  else return x86_unpack<P::g_size, *hi>(x, y);
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_repeated_128x2(P p, lanes_t<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( !P::repeated_16 ) return no_matching_shuffle;
  else if constexpr( auto r = shuffle_l2_x86_repeated_128x2_alignr(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_repeated_128x2_shuffle_ps(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_x86_repeated_128x2_unpack(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_within_128x2_shuffle_pd(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( P::g_size != 8 || P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( constexpr auto opt_mm = idxm::x86_shuffle_pd_2(P::idxs, P::reg_groups); !opt_mm )
  {
    return no_matching_shuffle;
  }
  else
  {
    using doubles_t = eve::wide<double, N * sizeof(T) / sizeof(double)>;
    auto x_f64     = bit_cast(x, eve::as<doubles_t> {});
    auto y_f64     = bit_cast(y, eve::as<doubles_t> {});

    constexpr int mm = *opt_mm;
    if constexpr( P::reg_size == 16 ) return _mm_shuffle_pd(x_f64, y_f64, mm);
    else if constexpr( P::reg_size == 32 ) return _mm256_shuffle_pd(x_f64, y_f64, mm);
    else return _mm512_shuffle_pd(x_f64, y_f64, mm);
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_within_128x2(P p, lanes_t<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( !idxm::shuffle_within_n(P::idxs, 16 / sizeof(T)) ) { return no_matching_shuffle; }
  else if constexpr( auto r = shuffle_l2_x86_within_128x2_shuffle_pd(p, g, x, y);
                     matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_permute2f128(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( P::g_size != 16 || P::reg_size != 32 ) return no_matching_shuffle;
  else
  {
    static_assert(!P::has_zeroes, "sanity check, no 0s/we or it's not two register");

    // insert is cheaper than permute2f128 (1 cycle latency and better on AMD)
    if constexpr( P::idxs[0] == 0 && P::idxs[1] == 2 ) return x86_insert_hi_128(x, y);
    else if constexpr( P::idxs[0] == 2 && P::idxs[1] == 0 ) return x86_insert_hi_128(y, x);
    else
    {
      constexpr int m = idxm::x86_permute2f128_mask(P::idxs);
      return _mm256_permute2f128_si256(x, y, m);
    }
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_shuffle_i32x4(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( sizeof(T) < 4 || P::reg_size < 64 ) return no_matching_shuffle;
  else if constexpr( constexpr auto m = idxm::mm512_shuffle_i64x2_idx(P::idxs); !m )
  {
    return no_matching_shuffle;
  }
  else
  {
    constexpr int mm = *m;
    return _mm512_shuffle_i64x2(x, y, mm);
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_shuffle_128_2regs(P p, lanes_t<G> g, wide<T, N> x, wide<T, N> y)
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

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_x86_alignr_epi32(P, lanes_t<G>, wide<T, N> x, wide<T, N> y)
{
  if constexpr( P::g_size < 4 ) return no_matching_shuffle;
  else if constexpr( current_api < avx512 ) return no_matching_shuffle;
  else if constexpr( constexpr auto starts_from = idxm::is_in_order(P::idxs); !starts_from )
  {
    return no_matching_shuffle;
  }
  else
  {
    static_assert(P::reg_size > 16, "sanity check - sse alignr is better");

    constexpr std::ptrdiff_t shift_epi32 = *starts_from * P::g_size / 4;
    constexpr std::ptrdiff_t shift_epi64 = *starts_from * P::g_size / 8;

    if constexpr( P::reg_size == 32 )
    {
      if constexpr( P::g_size >= 8 ) return _mm256_alignr_epi64(y, x, shift_epi64);
      else return _mm256_alignr_epi32(y, x, shift_epi32);
    }
    else
    {
      if constexpr( P::g_size >= 8 ) return _mm512_alignr_epi64(y, x, shift_epi64);
      else return _mm512_alignr_epi32(y, x, shift_epi32);
    }
  }
}

template<typename P, arithmetic_scalar_value T, width_type N, std::ptrdiff_t G>
 auto
shuffle_l2_(EVE_SUPPORTS(sse2_), P p, lanes_t<G> g, wide<T, N> x, wide<T, N> y)
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
  else if constexpr( auto r = shuffle_l2_x86_insert_ps(p, g, x, y); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}
}
