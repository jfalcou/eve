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

} // namespace idx

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_x86_128_8x2(wide<T, N> x, fixed<G>, pattern_t<I...>)
{
  constexpr std::array  idxs {I...};
  if constexpr( !idx::has_zeroes(idxs) )
  {
    if constexpr( std::same_as<T, double> )
    {
      constexpr int mm = idx::x86_mm_shuffle_2(idxs);
      return _mm_shuffle_pd(x, x, mm);
    }
    else
    {
      constexpr int mm = idx::x86_mm_shuffle_4(idxs);
      return _mm_shuffle_epi32(x, mm);
    }
  }
  // has zeroes
  else
  {
    if constexpr( idx::matches(idxs, {na_, 0}, {1, na_}) )
    {
      __m128i u64x2 = eve::bit_cast(x, eve::as<__m128i> {});
      if constexpr( idxs[0] == na_ ) return _mm_bslli_si128(u64x2, 8);
      else return _mm_bsrli_si128(u64x2, 8);
    }
    else if constexpr ( current_api >= sse4_1 )
    {
      // 0, na_ or na_, 1
      __m128i u64x2 = eve::bit_cast(x, eve::as<__m128i> {});
      return  _mm_insert_epi64(u64x2, 0, idxs[0] == na_ ? 0 : 1);
    }
    else return no_matching_shuffle;
  }
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_impl_(EVE_SUPPORTS(sse2_), wide<T, N> x, fixed<G> g, pattern_t<I...> p)
requires std::same_as<abi_t<T, N>, x86_128_>
{
  constexpr std::array idxs {I...};

  if constexpr( idx::is_identity(idxs) ) return x;
  else if constexpr( idx::is_zero(idxs) ) return wide<T, N> {0};
  else if constexpr( sizeof(T) == 8 ) return shuffle_l0_x86_128_8x2(x, g, p);
  else return no_matching_shuffle;
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l0_impl_(EVE_SUPPORTS(avx_), wide<T, N> x, fixed<G>, pattern_t<I...>)
requires std::same_as<abi_t<T, N>, x86_256_> && (sizeof...(I) * G == N::value)
{
  constexpr std::array  idxs {I...};
  constexpr std::size_t gsize = sizeof(T) * G;

  if constexpr( idx::is_identity(idxs) ) return x;
  else if constexpr( idx::is_zero(idxs) ) return wide<T, N> {0};
  else if constexpr( current_api >= avx2 && gsize >= 8 && !idx::has_zeroes(idxs) )
  {
    constexpr int shuffle = idx::x86_mm_shuffle_4(idxs);
    if constexpr( std::same_as<T, double> ) return _mm256_permute4x64_pd(x, shuffle);
    else return _mm256_permute4x64_epi64(x, shuffle);
  }
  else if constexpr( gsize == 16 )
  {
    constexpr int mm = idx::permute2f128_one_reg_mask(idxs);
    if constexpr( std::same_as<T, double> ) return _mm256_permute2f128_pd(x, x, mm);
    else return _mm256_permute2f128_si256(x, x, mm);
  }
  else if constexpr( idx::within_lane(idxs) && gsize == 8 && !idx::has_zeroes(idxs) )
  {
    constexpr int mm = idx::x86_shuffle_4_in_lane(idxs);
    return _mm256_permute_pd(x, mm);
  }
  else return no_matching_shuffle;
}
}
