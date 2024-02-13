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

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE wide<T, N>
                sve_tbl(wide<T, N> x, pattern_t<I...>)
{
  wide<T, N> table {I...};
 return svtbl(x, table);
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t... I>
EVE_FORCEINLINE wide<T, N>
                sve_tbl2(wide<T, N> x, wide<T, N> y, pattern_t<I...>)
{
  return svtbl2(svcreate2(x, y), wide<T, N>{I...});
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_svetbl(P, fixed<G>, wide<T, N> x)
{
  constexpr auto table_idxs =
      idxm::to_pattern<idxm::expand_group<G>(idxm::replace_we(P::idxs, eve::na_))>();

  return sve_tbl(x, table_idxs);
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l3_(EVE_SUPPORTS(sve_), P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( auto r = shuffle_l3_and_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else if constexpr ( auto r = shuffle_l3_slide_with_0(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else return shuffle_l3_svetbl(p, g, x);
}

}
