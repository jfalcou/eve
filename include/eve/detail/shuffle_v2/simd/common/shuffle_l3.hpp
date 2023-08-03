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
shuffle_l3_and_0(P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( !idxm::is_just_zeroes_replaced(P::idxs) ) return no_matching_shuffle;
  else
  {
    return x & is_na_or_we_mask(p, g, eve::as(x));
  }
}

}
