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
    constexpr auto pshuvb_pattern = idxm::x86_pshuvb_pattern<P::g_size>(P::idxs);
    if constexpr( !pshuvb_pattern ) return no_matching_shuffle;
    else
    {
      using u8xN = wide<std::uint8_t, eve::fixed<P::reg_size>>;
      return x86_pshuvb(idxm::to_pattern<*pshuvb_pattern>(), eve::bit_cast(x, eve::as<u8xN> {}));
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_x86_permutex(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( current_api < avx2 || P::reg_size < 32 ) return no_matching_shuffle;
  else if constexpr( P::g_size < 4 && current_api == avx2 ) return no_matching_shuffle;
  else if constexpr( P::g_size < 2 ) return no_matching_shuffle;
  else if constexpr( !P::has_zeroes )
  {
    auto idxs = make_idx_mask<P::idxs>(as(x));

    if constexpr( P::g_size == 2 )
    {
      if constexpr( P::reg_size == 32 ) return _mm256_permutexvar_epi16(idxs, x);
      else return _mm512_permutexvar_epi16(idxs, x);
    }
    else if constexpr( P::g_size == 4 )
    {
      if constexpr( P::reg_size == 32 ) return _mm256_permutevar8x32_epi32(x, idxs);
      else return _mm512_permutexvar_epi32(idxs, x);
    }
    else // >= 8
    {
      static_assert(P::reg_size == 64, "sanity chec, 64x4 is l2");
      return _mm512_permutexvar_epi64(idxs, x);
    }
  }
  else if constexpr( current_api < avx512 ) return no_matching_shuffle;
  else
  {
    auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage().value;
    auto idxs = make_idx_mask<P::idxs>(as(x));

    if constexpr( P::g_size == 2 )
    {
      if constexpr( P::reg_size == 32 ) return _mm256_maskz_permutexvar_epi16(mask, idxs, x);
      else return _mm512_maskz_permutexvar_epi16(mask, idxs, x);
    }
    else if constexpr( P::g_size == 4 )
    {
      if constexpr( P::reg_size == 32 ) return _mm256_maskz_permutexvar_epi32(mask, idxs, x);
      else return _mm512_maskz_permutexvar_epi32(mask, idxs, x);
    }
    else // >= 8
    {
      static_assert(P::reg_size == 64, "sanity chec, 64x4 is l2");
      return _mm512_maskz_permutexvar_epi64(mask, idxs, x);
    }
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
  else if constexpr( auto r = shuffle_l3_x86_permutex(p, g, x); matched_shuffle<decltype(r)> )
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
shuffle_l3_x86_permutex2(P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( current_api < avx512 || P::g_size == 1 ) return no_matching_shuffle;
  else if constexpr( !P::has_zeroes )
  {
    auto idxs = make_idx_mask<P::idxs>(as(x));

    if constexpr( P::g_size == 2 )
    {
      if constexpr( P::reg_size == 16 ) return _mm_permutex2var_epi16(x, idxs, y);
      else if constexpr( P::reg_size == 32 ) return _mm256_permutex2var_epi16(x, idxs, y);
      else return _mm512_permutex2var_epi16(x, idxs, y);
    }
    else if constexpr( P::g_size == 4 )
    {
      if constexpr( P::reg_size == 16 ) return _mm_permutex2var_epi32(x, idxs, y);
      else if constexpr( P::reg_size == 32 ) return _mm256_permutex2var_epi32(x, idxs, y);
      else return _mm512_permutex2var_epi32(x, idxs, y);
    }
    else // >= 8
    {
      static_assert(P::reg_size > 16, "sanity check, should be l2");
      if constexpr( P::reg_size == 32 ) return _mm256_permutex2var_epi64(x, idxs, y);
      else return _mm512_permutex2var_epi64(x, idxs, y);
    }
  }
  else
  {
    auto mask = is_na_or_we_logical_mask(p, g, as(x)).storage().value;
    auto idxs = make_idx_mask<P::idxs>(as(x));

    if constexpr( P::g_size == 2 )
    {
      if constexpr( P::reg_size == 16 ) return _mm_maskz_permutex2var_epi16(mask, x, idxs, y);
      else if constexpr( P::reg_size == 32 )
        return _mm256_maskz_permutex2var_epi16(mask, x, idxs, y);
      else return _mm512_maskz_permutex2var_epi16(mask, x, idxs, y);
    }
    else if constexpr( P::g_size == 4 )
    {
      if constexpr( P::reg_size == 16 ) return _mm_maskz_permutex2var_epi32(mask, x, idxs, y);
      else if constexpr( P::reg_size == 32 )
        return _mm256_maskz_permutex2var_epi32(mask, x, idxs, y);
      else return _mm512_maskz_permutex2var_epi32(mask, x, idxs, y);
    }
    else // >= 8
    {
      static_assert(P::reg_size > 16, "sanity check, shouldn't happen");
      if constexpr( P::reg_size == 32 ) return _mm256_maskz_permutex2var_epi64(mask, x, idxs, y);
      else return _mm512_maskz_permutex2var_epi64(mask, x, idxs, y);
    }
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l3_x86_blendv(p, g, x, y); matched_shuffle<decltype(r)> ) return r;
  else if constexpr( auto r = shuffle_l3_x86_permutex2(p, g, x, y); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

}
