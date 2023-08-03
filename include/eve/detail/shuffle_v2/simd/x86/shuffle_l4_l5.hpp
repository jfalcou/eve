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

template<typename P, typename T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_x86_shorts_lo_hi(P, fixed<G>, wide<T, N> x)
{
  if constexpr( P::g_size < 2 || P::has_zeroes || !idxm::shuffle_within_halves(P::idxs))
  {
    return kumi::tuple {no_matching_shuffle, eve::index<-1>};
  }
  else
  {
    constexpr auto lo_hi = idxm::shuffle_halves_independetly(P::idxs);
    x                    = shuffle_l<2>(x, idxm::to_pattern<lo_hi[0]>());
    x                    = shuffle_l<2>(x, idxm::to_pattern<lo_hi[1]>());
    return kumi::tuple{x, eve::index<4>};
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_128_> && (P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l4_x86_shorts_lo_hi(p, g, x);
                matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
