//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/minmax.hpp>
#include <eve/module/core/named_shuffles/swap_adjacent.hpp>
#include <eve/module/core/named_shuffles/blend.hpp>

namespace eve::detail
{

// Building up, then going down.
// 0, 1, 1, 0, 0, 1, 1, 0 ...
template <std::ptrdiff_t Full>
constexpr auto bitonic_merge_blend_pattern = [](int i, int) {
  int turn = i / Full;
  bool is_odd_turn = turn % 2;
  return (i + is_odd_turn) % 2;
};

template <simd_value T, typename Less, std::ptrdiff_t Full, std::ptrdiff_t G>
EVE_FORCEINLINE
T bitonic_merge_impl(T x, Less less, fixed<Full> full, fixed<G> g)
{
  if constexpr ( G == 0 ) return x;
  else
  {
    T ab = x;
    T ba = eve::swap_adjacent(ab, g);
    auto [aa, bb] = minmax(less)(ab, ba);
    x = blend(aa, bb, g, bitonic_merge_blend_pattern<Full / G>);
    return bitonic_merge_impl(x, less, full, lane<G / 2>);
  }
}

// G is the lenght of the monotonic sequence
template <simd_value T, typename Less, std::ptrdiff_t G>
EVE_FORCEINLINE
T bitonic_merge(T x, Less less, fixed<G>)
{
  return bitonic_merge_impl(x, less, lane<G * 2>, eve::lane<G>);
}

// G - length of monotonic sequence
template <simd_value T, typename Less, std::ptrdiff_t G>
EVE_FORCEINLINE
T make_bitonic(T x, Less less, fixed<G>)
{
  if constexpr (G < 1) return x;
  else
  {
    x = make_bitonic(x, less, lane<G / 2>);
    return bitonic_merge(x, less, lane<G / 2>);
  }
}

template <simd_value T, typename Less>
EVE_FORCEINLINE
T sort_(EVE_SUPPORTS(cpu_), T x, Less less)
{
  return make_bitonic(x, less, eve::lane<T::size()>);
}

template <simd_value T>
EVE_FORCEINLINE
T sort_(EVE_SUPPORTS(cpu_), T x)
{
  return sort(x, eve::is_less);
}
}
