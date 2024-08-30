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
template<typename P, scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(rvv_), P p, fixed<G> g, wide<T, N> x)
{
  using int_ty = as_integer_t<T, unsigned>;
  if constexpr( G == N::value )
  {
    wide<as_integer_t<T, unsigned>, N> offsets(P::idxs);
    wide<T, N>                         res = __riscv_vrgather_tu(x, x, offsets.storage(), N::value);
    return res;
  }
  else
  {
    std::array<int_ty, N::value> ids;
    for( auto id = 0; id < N::value; ++id )
    {
      size_t id_from_pattern = id / G;
      ids[id]                = P::idxs[id_from_pattern] * G + id % G;
    }
    wide<as_integer_t<T, unsigned>, N> offsets(ids);
    wide<T, N>                         res = __riscv_vrgather_tu(x, x, offsets.storage(), N::value);
    return res;
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(rvv_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
{
  if constexpr( !idxm::is_blend(P::idxs, N::value / G) ) return no_matching_shuffle;
  else
  {
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] < size / G; });
    auto                     ret = if_else(m, x, y);
    // there we not have zeroing indexes, add zeros.
    wide<T, N>               zeros(0);
    eve::logical<wide<T, N>> not_zero([](int i, int size) { return P::idxs[i / G] != na_; });
    return if_else(not_zero, ret, zeros);
  }
}

}
