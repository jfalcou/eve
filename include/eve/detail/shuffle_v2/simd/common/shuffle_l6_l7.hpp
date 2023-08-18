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

template<typename P, logical_simd_value T, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l6_l7_blend_nonwide_logicals(P, fixed<G>, T x, T y)
{
  if constexpr( !idxm::is_blend(P::idxs, T::size() / G) )
  {
    return kumi::tuple {no_matching_shuffle, eve::index<-1>};
  }
  else
  {
    T m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    return kumi::tuple {(x && !m) || (y && m), eve::index<6>};
  }
}

// common non wide logical thinking
template<typename P, logical_simd_value T, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l6_l7_(EVE_SUPPORTS(cpu_), P p, fixed<G> g, T x, T y)
{
  if constexpr( auto r = shuffle_l6_l7_blend_nonwide_logicals(p, g, x, y);
                matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

}
