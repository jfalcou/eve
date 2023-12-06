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

// For now didn't figure out how to generalize
template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_neon_reverse(P, fixed<G> g, wide<T, N> x)
{
  if constexpr( !idxm::is_reverse(P::idxs) )
    return kumi::tuple {no_matching_shuffle, eve::index<-1>};
  else
  {
    // swap havles and reverse halves
    x = shuffle_l<2>(x, eve::lane<8 / sizeof(T)>, eve::pattern<1, 0>);

    // halve reverse is already computed
    constexpr auto within8 = get<1>(*P::shuffle_8_first);
    x                      = shuffle_l<2>(x, eve::lane<G>, idxm::to_pattern<within8>());
    return kumi::tuple {x, eve::index<4>};
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_neon_extract_dup(P, fixed<G>, wide<T, N> x)
{
  constexpr auto lane = idxm::is_lane_broadcast(P::idxs);

  if constexpr ( !lane ) return kumi::tuple {no_matching_shuffle, eve::index<-1>};
  else
  {
    // not broadcast_lane_set_get because we want a compile time index.
    // NOTE: maybe better to extract a simd value and then dupq_lane
    constexpr std::ptrdiff_t m = *lane;
    if constexpr( sizeof(T) == 1 ) x = vgetq_lane_u8(x, m);
    else if constexpr( sizeof(T) == 2 ) x = vgetq_lane_u16(x, m);
    else if constexpr( sizeof(T) == 4 ) x = vgetq_lane_u32(x, m);
    else if constexpr( sizeof(T) == 8 ) x = vgetq_lane_u64(x, m);
    return kumi::tuple {x, eve::index<4>};
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_(EVE_SUPPORTS(neon128_), P p, fixed<G> g, wide<T, N> x)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l4_l5_neon_reverse(p, g, x); matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l4_neon_extract_dup(p, g, x); matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
