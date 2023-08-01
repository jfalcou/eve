//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/shuffle_v2/shuffle_l2.hpp>
#include <eve/detail/shuffle_v2/shuffle_l3.hpp>

namespace eve::detail
{

template<std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
native_shuffle_lookup_(EVE_SUPPORTS(cpu_),
                       pattern_t<I...>    p,
                       fixed<G>           g,
                       auto ... xs)
{
  // l0 and l1 are handled by the driver
  if constexpr( auto r0 = invoke_shuffle(shuffle_l2, p, g, xs...); matched_shuffle<decltype(r0)> )
  {
    return kumi::tuple {r0, eve::index<2>};
  }
  else if constexpr( auto r0 = invoke_shuffle(shuffle_l3, p, g, xs...); matched_shuffle<decltype(r0)> )
  {
    return kumi::tuple {r0, eve::index<3>};
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}
}
