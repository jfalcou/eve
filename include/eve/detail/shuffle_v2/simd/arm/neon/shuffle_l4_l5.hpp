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
shuffle_l4_l5_(EVE_SUPPORTS(neon128_), P p, fixed<G> g, wide<T, N> x)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l4_l5_neon_reverse(p, g, x); matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
