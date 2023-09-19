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

template<std::ptrdiff_t ToTry, typename P>
constexpr bool
shuffle_l_fallback_try_sse2_group_plus_u8(P)
{
  constexpr auto group_within = P::shuffle_n_first(eve::lane<ToTry>);

  if constexpr( !group_within ) return false;
  else
  {
    constexpr auto most_repeated = idxm::most_repeated_pattern_a<get<1>(*group_within)>;

    if (idxm::is_rotate(most_repeated)) return true;
    if (idxm::is_slide_left(most_repeated)) return true;
    return false;
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l_fallback_sse2_uN_u8(P, fixed<G> g, wide<T, N> x)
{
  constexpr auto match = []()
  {
    if ( shuffle_l_fallback_try_sse2_group_plus_u8<8>(P {}) ) return 8;
    if ( shuffle_l_fallback_try_sse2_group_plus_u8<4>(P{}) ) return 4;
    if ( shuffle_l_fallback_try_sse2_group_plus_u8<2>(P{}) ) return 2;
    return -1;
  }();

  if constexpr( match == -1 ) return kumi::tuple {no_matching_shuffle, eve::index<-1>};
  else
  {
    constexpr auto groups_within = *P::shuffle_n_first(eve::lane<match>);
    constexpr auto groups_p = idxm::to_pattern<get<0>(groups_within)>();
    constexpr auto within_p = idxm::to_pattern<get<1>(groups_within)>();

    auto [groups, groups_l] = shuffle_v2_core(x, eve::lane<match>, groups_p);
    auto [res, within_l]    = shuffle_v2_core(groups, g, within_p);
    return kumi::tuple {res, idxm::add_shuffle_levels(groups_l, within_l)};
  }
}

// sse2 char shuffles
template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l_fallback_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_128_> && (P::out_reg_size == P::reg_size)
         && (current_api < ssse3) && (P::g_size == 1)
{
  if constexpr( auto r = shuffle_l_fallback_sse2_uN_u8(p, g, x);
                matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return no_matching_shuffle;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l_fallback_(EVE_SUPPORTS(avx_), P p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_256_> && (P::out_reg_size == P::reg_size) && (P::g_size <= 2)
         && (current_api == avx)
{
  auto lo_hi     = x.slice();
  auto p_lo_p_hi = idxm::slice_pattern<N() / 2>(p);

  auto lo   = get<0>(lo_hi);
  auto hi   = get<1>(lo_hi);
  auto p_lo = get<0>(p_lo_p_hi);
  auto p_hi = get<1>(p_lo_p_hi);

  if constexpr(
      requires { shuffle_v2_core(lo, hi, g, p_lo); }
      && requires { shuffle_v2_core(lo, hi, g, p_hi); } )
  {
    auto [shuffled_lo, lo_l] = shuffle_v2_core(lo, hi, g, p_lo);
    auto [shuffled_hi, hi_l] = shuffle_v2_core(lo, hi, g, p_hi);

    x = wide<T, N> {shuffled_lo, shuffled_hi};

    // 4 to extract + combine
    return kumi::tuple {x, idxm::add_shuffle_levels(lo_l, hi_l, eve::index<4>)};
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l_fallback_(EVE_SUPPORTS(avx_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires std::same_as<abi_t<T, N>, x86_256_> && (P::out_reg_size == P::reg_size) && (P::g_size <= 2)
         && (current_api == avx)
{
  auto x_01 = x.slice();
  auto y_01 = y.slice();
  auto p_01 = idxm::slice_pattern<N() / 2>(p);

  auto x0 = get<0>(x_01);
  auto x1 = get<1>(x_01);
  auto y0 = get<0>(y_01);
  auto y1 = get<1>(y_01);
  auto p0 = get<0>(p_01);
  auto p1 = get<1>(p_01);

  if constexpr(
      requires { shuffle_v2_core(x0, x1, y0, y1, g, p0); }
      && requires { shuffle_v2_core(x0, x1, y0, y1, g, p1); } )
  {
    auto [shuffled0, l0] = shuffle_v2_core(x0, x1, y0, y1, g, p0);
    auto [shuffled1, l1] = shuffle_v2_core(x0, x1, y0, y1, g, p1);

    x = wide<T, N> {shuffled0, shuffled1};

    // 4 to extract + combine
    return kumi::tuple {x, idxm::add_shuffle_levels(l0, l1, eve::index<4>)};
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
