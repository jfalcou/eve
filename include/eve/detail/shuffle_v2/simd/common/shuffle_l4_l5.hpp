//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/detail/shuffle_v2/shuffle_v2_driver_fwd.hpp>

namespace eve::detail
{

template<typename P, simd_value T, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_broadcast_lane_set_get(P, fixed<G>, T x)
{
  constexpr auto lane = idxm::is_lane_broadcast(P::idxs);

  if constexpr( !lane || G > 1 ) return kumi::tuple {no_matching_shuffle, eve::index<-1>};
  else return kumi::tuple {T {x.get(*lane)}, eve::index<4>};
}

}
