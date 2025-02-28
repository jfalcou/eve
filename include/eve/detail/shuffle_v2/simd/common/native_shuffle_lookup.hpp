//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/native_shuffle_helpers.hpp>
#include <eve/detail/shuffle_v2/shuffle_l2.hpp>
#include <eve/detail/shuffle_v2/shuffle_l3.hpp>
#include <eve/detail/shuffle_v2/shuffle_l4_l5.hpp>
#include <eve/detail/shuffle_v2/shuffle_l6_l7.hpp>
#include <eve/detail/shuffle_v2/shuffle_l_fallback.hpp>

namespace eve::detail
{

template<typename T, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
native_shuffle_lookup_(EVE_SUPPORTS(cpu_), pattern_t<I...>, fixed<G> g, T x, auto... xs)
{
  constexpr auto p = expanded_pattern<T, G, I...>;

  // l0 and l1 are handled by the driver
  if constexpr( auto r0 = invoke_shuffle(shuffle_l2, p, g, x, xs...); matched_shuffle<decltype(r0)> )
  {
    return kumi::tuple {r0, eve::index<2>};
  }
  else if constexpr( auto r1 = invoke_shuffle(shuffle_l3, p, g, x, xs...);
                     matched_shuffle<decltype(r1)> )
  {
    return kumi::tuple {r1, eve::index<3>};
  }
  else if constexpr( auto r2 = invoke_shuffle_multilevel(shuffle_l4_l5, p, g, x, xs...);
                     matched_shuffle<decltype(get<0>(r2))> )
  {
    return r2;
  }
  else if constexpr( auto r3 = invoke_shuffle_multilevel(shuffle_l6_l7, p, g, x, xs...);
                     matched_shuffle<decltype(get<0>(r3))> )
  {
    return r3;
  }
  else if constexpr( auto r4 = invoke_shuffle_multilevel(shuffle_l_fallback, p, g, x, xs...);
                     matched_shuffle<decltype(get<0>(r4))> )
  {
    return r4;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}
}
