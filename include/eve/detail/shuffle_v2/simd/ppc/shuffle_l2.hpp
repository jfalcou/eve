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
auto
shuffle_l2_ppc_vec_splat(P, eve::fixed<G>, eve::wide<T, N> x)
{
  constexpr auto lane = idxm::is_lane_broadcast(P::idxs);

  if constexpr( !lane || G > 1 ) return no_matching_shuffle;
  else
  {
    constexpr std::ptrdiff_t m = *lane;
    return vec_splat(x.storage(), m);
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(vmx_), P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( auto r = shuffle_l2_element_bit_shift(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l2_ppc_vec_splat(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle_t {};
}

}
