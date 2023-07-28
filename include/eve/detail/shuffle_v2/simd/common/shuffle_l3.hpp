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

template<typename T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l3_and_0(pattern_t<I...> p, fixed<G>, wide<T, N> x)
{
  constexpr std::array idxs {I...};
  if constexpr( !idxm::is_just_zeroes_replaced(idxs) ) return no_matching_shuffle;
  else if constexpr( G != 1 )
  {
    return shuffle_l3_and_0(p, idxm::to_pattern<expand_group<G>(idxs)>(), x);
  }
  else
  {
    wide<T, N> mask {(I < 0 ? 0 : (T)-1)...};
    return x & mask;
  }
}

}
