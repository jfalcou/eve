//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>

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

  constexpr int x86_shuffle_4_in_lane(std::span<const std::ptrdiff_t, 4> idxs)
  {
    // we_ doesn't affect here
    int res = 0;
    if( idxs[0] == 1 ) res |= 1;
    if( idxs[1] == 1 ) res |= 1 << 1;
    if( idxs[2] == 3 ) res |= 1 << 2;
    if( idxs[3] == 3 ) res |= 1 << 3;
    return res;
  }

  constexpr int x86_mm_shuffle_2(std::span<const std::ptrdiff_t, 2> _idxs)
  {
    auto idxs = replace_we(_idxs, 0);
    return _MM_SHUFFLE2(idxs[1], idxs[0]);
  }

  constexpr int x86_mm_shuffle_4(std::span<const std::ptrdiff_t, 2> _idxs)
  {
    std::array<std::ptrdiff_t, 2> idxs = replace_we(_idxs, 0);
    idxs[0] *= 2;
    idxs[1] *= 2;
    return _MM_SHUFFLE(idxs[1] + 1, idxs[1], idxs[0] + 1, idxs[0]);
  }

  constexpr int x86_mm_shuffle_4(std::span<const std::ptrdiff_t, 4> _idxs)
  {
    std::array<std::ptrdiff_t, 4> idxs = replace_we(_idxs, 0);
    return _MM_SHUFFLE(idxs[3], idxs[2], idxs[1], idxs[0]);
  }

  constexpr int permute2f128_one_reg_mask(std::span<const std::ptrdiff_t, 2> _idxs)
  {
    auto idxs = replace_we(_idxs, 0);
    if( idxs[0] == na_ ) idxs[0] = 0xf;
    if( idxs[1] == na_ ) idxs[1] = 0xf;
    return idxs[0] | idxs[1] << 4;
  }

  constexpr int blend_immediate_mask(std::span<const std::ptrdiff_t> idxs)
  {
    int r = 0;
    int s = std::ssize(idxs);
    for( int pos = 0; auto i : idxs )
    {
      // we_ < s
      if( i >= s ) { r |= 1 << pos; }
      ++pos;
    }
    return r;
  }

} // namespace idx

/*
 * 16 byte shuffles that were duplicated in next arches between multiple lanes.
 */
template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_x86_within_128(pattern_t<I...>, fixed<G> g, wide<T, N> x)
{
  constexpr std::array  idxs {I...};
  constexpr std::size_t reg_size = sizeof(T) * N::value;
  constexpr bool        zeroes   = idxm::has_zeroes(idxs);

  if constexpr( idxs.size() * G * sizeof(T) > 16 )
  {
    constexpr auto p_half = idxm::is_repeating_pattern(idxs);

    if constexpr( !p_half ) return no_matching_shuffle;
    else return shuffle_l0_x86_within_128(idxm::to_pattern<*p_half>(), g, x);
  }
  else if constexpr( sizeof(T) >= 4 && !zeroes )
  {
    constexpr int m = idx::x86_mm_shuffle_4(idxs);

    if constexpr( reg_size == 16 ) return _mm_shuffle_epi32(x, m);
    else if constexpr( reg_size == 32 )
    {
      // _mm256_shuffle_epi32 has better throughput
      if constexpr( current_api >= avx2 ) return _mm256_shuffle_epi32(x, m);
      else return _mm256_permute_ps(eve::bit_cast(x, eve::as<__m256> {}), m);
    }
    else if constexpr( reg_size == 64 ) return _mm512_shuffle_epi32(x, m);
  }
  else if constexpr( constexpr auto rotation = idxm::is_rotate(idxs);
                     rotation
                     && ((current_api >= ssse3 && reg_size == 16)
                         || (current_api >= avx2 && reg_size == 32)) )
  {
    constexpr int m = 16 - G * sizeof(T) * *rotation;

    if constexpr( reg_size == 16 ) return _mm_alignr_epi8(x, x, m);
    else if constexpr( reg_size == 32 ) return _mm256_alignr_epi8(x, x, m);
    else if constexpr( reg_size == 64 ) return _mm512_alignr_epi8(x, x, m);
  }
  else return no_matching_shuffle;
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_x86_128_8x2(pattern_t<I...>, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs {I...};
  if constexpr( idx::matches(idxs, {0, na_}) ) return _mm_move_epi64(x);
  else if constexpr( idx::matches(idxs, {na_, 0}, {1, na_}) )
  {
    if constexpr( idxs[0] == na_ ) return _mm_bslli_si128(x, 8);
    else return _mm_bsrli_si128(x, 8);
  }
  else if constexpr( current_api >= sse4_1 )
  {
    // na_, 1
    return _mm_insert_epi64(x, 0, 1);
  }
  else return no_matching_shuffle;
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_impl_(EVE_SUPPORTS(sse2_), pattern_t<I...> p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_128_>
{
  constexpr std::array idxs {I...};

  if constexpr( idxs.size() * G != N::value ) return no_matching_shuffle;
  else if constexpr( idx::is_identity(idxs) ) return x;
  else if constexpr( idx::is_zero(idxs) ) return wide<T, N> {0};
  else if constexpr( matched_shuffle<decltype(shuffle_l0_x86_within_128(p, g, x))> )
  {
    return shuffle_l0_x86_within_128(p, g, x);
  }
  else if constexpr( sizeof(T) == 8 ) return shuffle_l0_x86_128_8x2(p, g, x);
  else return no_matching_shuffle;
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_impl_(EVE_SUPPORTS(avx_), pattern_t<I...> p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_256_> && (sizeof...(I) * G == N::value)
{
  constexpr std::array  idxs {I...};
  constexpr std::size_t gsize = sizeof(T) * G;

  if constexpr( idxs.size() * G != N::value ) return no_matching_shuffle;
  else if constexpr( idx::is_identity(idxs) ) return x;
  else if constexpr( idx::is_zero(idxs) ) return wide<T, N> {0};
  else if constexpr( matched_shuffle<decltype(shuffle_l0_x86_within_128(p, g, x))> )
  {
    return shuffle_l0_x86_within_128(p, g, x);
  }
  else if constexpr( current_api >= avx2 && gsize >= 8 && !idxm::has_zeroes(idxs) )
  {
    constexpr int shuffle = idx::x86_mm_shuffle_4(idxs);
    return _mm256_permute4x64_epi64(x, shuffle);
  }
  else if constexpr( gsize == 16 )
  {
    constexpr int mm = idx::permute2f128_one_reg_mask(idxs);
    return _mm256_permute2f128_si256(x, x, mm);
  }
  else if constexpr( idx::within_lane(idxs) && gsize == 8 && !idxm::has_zeroes(idxs) )
  {
    constexpr int mm = idx::x86_shuffle_4_in_lane(idxs);
    return _mm256_permute_pd(eve::bit_cast(x, eve::as<__m256d> {}), mm);
  }
  else return no_matching_shuffle;
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_impl_(EVE_SUPPORTS(sse2_), pattern_t<I...>, fixed<G>, wide<T, N> y, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_128_>
{
  constexpr std::array idxs {I...};

  if constexpr( idxs.size() * G != N::value ) return no_matching_shuffle;
  // Immediate blends are very good, even if are covered by other ops
  // https://stackoverflow.com/questions/76552874/how-should-i-chose-between-mm-move-sd-mm-shuffle-pd-mm-blend-pd
  //
  // FIX-1617 - enable `_mm_blend_epi16`
  else if constexpr( eve::current_api >= eve::sse4_1 && sizeof(T) >= 4 && idx::is_blend(idxs) )
  {
    constexpr int m = idx::blend_immediate_mask(idxs);

    if constexpr( sizeof(T) == 8 )
    {
      auto x_f64 = bit_cast(x, eve::as<__m128d> {});
      auto y_f64 = bit_cast(y, eve::as<__m128d> {});
      return _mm_blend_pd(x_f64, y_f64, m);
    }
    else if constexpr( sizeof(T) == 4 )
    {
      auto x_f32 = bit_cast(x, eve::as<__m128> {});
      auto y_f32 = bit_cast(y, eve::as<__m128> {});
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
    auto x_f64 = bit_cast(x, eve::as<__m128d> {});
    auto y_f64 = bit_cast(y, eve::as<__m128d> {});

    // There is also _mm_move_sd but there is no reason to generate it for us.
    // Compiler sometimes transforms.
    constexpr int m = _MM_SHUFFLE2(idxs[1] - 2, idxs[0]);
    return _mm_shuffle_pd(x_f64, y_f64, m);
  }
  else return no_matching_shuffle;
}
}
