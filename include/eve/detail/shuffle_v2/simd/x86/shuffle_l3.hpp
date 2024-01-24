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

template<typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
x86_pshuvb(pattern_t<I...>, wide<std::uint8_t, N> x)
{
  wide<std::uint8_t, N> mask {I...};
  if constexpr( N() == 16 ) return _mm_shuffle_epi8(x, mask);
  else if constexpr( N() == 32 ) return _mm256_shuffle_epi8(x, mask);
  else return _mm512_shuffle_epi8(x, mask);
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_x86_pshuvb(P, fixed<G>, wide<T, N> x)
{
  if constexpr( current_api < ssse3 ) return no_matching_shuffle;
  else if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
  else
  {
    constexpr auto pshuvb_pattern = idxm::x86_pshuvb_pattern<G * sizeof(T)>(P::idxs);
    if constexpr (!pshuvb_pattern) return no_matching_shuffle;
    else
    {
      using u8xN = wide<std::uint8_t, eve::fixed<P::reg_size>>;
      return x86_pshuvb(idxm::to_pattern<*pshuvb_pattern>(), eve::bit_cast(x, eve::as<u8xN> {}));
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_x86_perm(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( current_api < avx2 || P::reg_size < 32 ) return no_matching_shuffle;
  else if constexpr( P::g_size < 4 ) return no_matching_shuffle;
  // on avx512 masked version on 256 register a different instruction for some reason
  else if constexpr( P::reg_size == 32 && P::has_zeroes ) return no_matching_shuffle;
  else if constexpr( P::reg_size == 64 && P::has_zeroes )
  {
    auto zero_out = is_na_or_we_mask(p, g, eve::as<logical<wide<T, N>>> {}).storage().value;
    auto idxs     = make_idx_mask<P::idxs>(as(x));

    if constexpr( P::g_size == 4 ) return _mm512_maskz_permutexvar_epi32(zero_out, idxs, x);
    else if constexpr( P::g_size == 8 ) return _mm512_maskz_permutexvar_epi64(zero_out, idxs, x);
  }
  else
  {
    static_assert(G == 1, "we don't expect G > 1 to be here");

    auto idxs = make_idx_mask<P::idxs>(as(x));

    // epi64 handled before for 32 bytes
    if constexpr( P::reg_size == 32 ) return _mm256_permutevar8x32_epi32(x, idxs);
    else if constexpr( P::g_size == 4 ) return _mm512_permutexvar_epi32(idxs, x);
    else return _mm512_permutexvar_epi64(idxs, x);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_and_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else if constexpr( auto r = shuffle_l3_x86_pshuvb(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l3_x86_perm(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_x86_blendv(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  // avx512 should not be considered here at all
  if constexpr( current_api >= avx512 ) return no_matching_shuffle;
  else if constexpr( current_api < eve::sse4_1 || (current_api == eve::avx && P::reg_size == 32) )
  {
    return no_matching_shuffle;
  }
  else if constexpr( !idxm::is_blend(P::idxs, N::value / G) ) return no_matching_shuffle;
  else
  {
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    if constexpr( P::reg_size == 16 ) return _mm_blendv_epi8(x, y, m.bits());
    else return _mm256_blendv_epi8(x, y, m.bits());
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_x86_blendv(p, g, x, y); matched_shuffle<decltype(r)> ) return r;
  else return no_matching_shuffle;
}

}
