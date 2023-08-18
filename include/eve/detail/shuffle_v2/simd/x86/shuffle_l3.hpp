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
  if constexpr( N() == 16 )
  {
    wide<std::uint8_t, N> mask {I...};
    return _mm_shuffle_epi8(x, mask);
  }
  else if constexpr( N() == 32 )
  {
    wide<std::uint8_t, N> mask {I..., I...};
    return _mm256_shuffle_epi8(x, mask);
  }
  else
  {
    wide<std::uint8_t, N> mask {I..., I..., I..., I...};
    return _mm512_shuffle_epi8(x, mask);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_x86_pshuvb(P, fixed<G>, wide<T, N> x)
{
  if constexpr( current_api < ssse3 ) return no_matching_shuffle;
  else if constexpr( current_api == avx && P::reg_size == 32 ) return no_matching_shuffle;
  else if constexpr( !P::repeated_16 ) return no_matching_shuffle;
  else
  {
    constexpr auto no_we    = idxm::replace_we(*P::repeated_16, 0xff);
    constexpr auto no_na    = idxm::replace_na(no_we, 0xff);
    constexpr auto expanded = idxm::expand_group<P::g_size>(no_na);

    using u8xN = wide<std::uint8_t, eve::fixed<P::reg_size>>;

    return x86_pshuvb(idxm::to_pattern<expanded>(), eve::bit_cast(x, eve::as<u8xN> {}));
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
