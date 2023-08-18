//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{

template<typename P, simd_value T, std::ptrdiff_t G>
auto
shuffle_l2_svrev(P, eve::fixed<G>, T x)
{
  if constexpr( P::g_size > 8 || !idxm::is_reverse(P::idxs) ) return no_matching_shuffle;
  else if constexpr( arithmetic_simd_value<T> ) return T {svrev(x)};
  else
  {
    if constexpr( P::g_size == 1 ) return T {svrev_b8(x)};
    else if constexpr( P::g_size == 2 ) return T {svrev_b16(x)};
    else if constexpr( P::g_size == 4 ) return T {svrev_b32(x)};
    else if constexpr( P::g_size == 8 ) return T {svrev_b64(x)};
  }
}

template<typename P, typename T, typename N, std::ptrdiff_t G>
auto
shuffle_l2_svrevbhw(P p, eve::fixed<G> g, eve::wide<T, N> _x)
{
  constexpr std::ptrdiff_t reverse_size = P::most_repeated_no_zeroes.size() * P::g_size;
  if constexpr( reverse_size > 8 ) return no_matching_shuffle;
  else if constexpr( !idxm::is_reverse(P::most_repeated_no_zeroes) ) return no_matching_shuffle;
  else
  {
    auto x  = up_element_size_to(_x, eve::lane<reverse_size>);
    using U = decltype(x);

    if constexpr( !P::has_zeroes )
    {
      auto m = sve_true<T>();

      if constexpr( P::g_size == 1 ) return U {svrevb_x(m, x)};
      else if constexpr( P::g_size == 2 ) return U {svrevh_x(m, x)};
      else if constexpr( P::g_size == 4 ) return U {svrevw_x(m, x)};
    }
    else
    {
       // Didn't work out of the gate for some reason.
      (void)p;
      (void)g;
      return no_matching_shuffle;
#if 0
      auto m = is_na_or_we_mask(p, g, eve::as<eve::logical<eve::wide<T, N>>> {});

      if constexpr( P::g_size == 1 ) return U {svrevb_z(m, x)};
      else if constexpr( P::g_size == 2 ) return U {svrevh_z(m, x)};
      else if constexpr( P::g_size == 4 ) return U {svrevw_z(m, x)};
#endif
    }
  }
}

template<typename P, typename T, typename N, std::ptrdiff_t G>
auto
shuffle_l2_svext_self(P, eve::fixed<G>, eve::wide<T, N> x)
{
  constexpr auto point = idxm::is_rotate(P::idxs);
  if constexpr( !point ) return no_matching_shuffle;
  else
  {
    constexpr std::uint64_t m = (P::idxs.size() - *point) * G;
    x                         = svext(x, x, m);
    return x;
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sve_), P p, fixed<G> g, wide<T, N> x)
{
  if constexpr( auto r = shuffle_l2_svrev(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else if constexpr( auto r = shuffle_l2_svrevbhw(p, g, x); matched_shuffle<decltype(r)> ) return r;
  else if constexpr( auto r = shuffle_l2_svext_self(p, g, x); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sve_), P p, fixed<G> g, logical<wide<T, N>> x)
{
  if constexpr( auto r = shuffle_l2_svrev(p, g, x); matched_shuffle<decltype(r)> ) { return r; }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_sve_blend(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  // here using idxs, not idxs2match, no zeroing blend on sve
  if constexpr( !idxm::is_blend(P::idxs, N::value / G) ) return no_matching_shuffle;
  else
  {
    eve::logical<wide<T, N>> m([](int i, int size) { return P::idxs[i / G] >= size / G; });
    return wide<T, N> {svsel(m, y, x)};
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l2_(EVE_SUPPORTS(sve_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l2_sve_blend(p, g, x, y); matched_shuffle<decltype(r)> )
  {
    return r;
  }
  else return no_matching_shuffle_t {};
}

}
