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
shuffle_l4_x86_shorts_lo_hi(P, fixed<G>, wide<T, N> x)
{
  constexpr auto no = kumi::tuple {no_matching_shuffle, eve::index<-1>};

  if constexpr( P::reg_size == 32 && P::g_size <= 2 && current_api == avx ) return no;
  else if constexpr( P::g_size < 2 || P::has_zeroes ) return no;
  else if constexpr( !P::repeated_16 || !idxm::shuffle_within_halves(*P::repeated_16) ) return no;
  else
  {
    static_assert(G == 1, "validating expectation");
    constexpr std::size_t to_repeat = P::reg_size / 16;
    constexpr auto        lo_hi     = idxm::shuffle_halves_independetly(*P::repeated_16);
    constexpr auto        lo_p      = idxm::repeat<to_repeat>(lo_hi[0]);
    constexpr auto        hi_p      = idxm::repeat<to_repeat>(lo_hi[1]);
    x                               = shuffle_l<2>(x, idxm::to_pattern<lo_p>());
    x                               = shuffle_l<2>(x, idxm::to_pattern<hi_p>());
    return kumi::tuple {x, eve::index<4>};
  }
}

// First shuffle 16 byte lanes and then shuffle the in betweeny thingies.
// Only works for repeated patterns.
template<typename P, typename T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_x86_put_u64x2_in_position(P, fixed<G>, wide<T, N> x)
{
  constexpr auto no = kumi::tuple {no_matching_shuffle, eve::index<-1>};
  if constexpr( P::reg_size < 32 ) return no;
  // there is nothing we can do for shorts on avx
  else if constexpr( P::reg_size == 32 && P::g_size <= 2 && current_api == avx ) return no;
  else if constexpr( P::has_zeroes && current_api < avx2 ) return no;
  else if constexpr( !P::shuffle_16in16 ) return no;
  else
  {
    constexpr auto p0 = get<0>(*P::shuffle_16in16);
    constexpr auto p1 = get<1>(*P::shuffle_16in16);
    auto [r0, l0]     = shuffle_v2_core(x, eve::lane<G>, idxm::to_pattern<p0>());
    auto [r1, l1]     = shuffle_v2_core(r0, eve::lane<G>, idxm::to_pattern<p1>());

    return kumi::tuple {r1, idxm::add_shuffle_levels(l0, l1)};
  }
}

template<typename P, typename T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_x86_slide_less_than_16(P, fixed<G>, wide<T, N> x)
{
  constexpr auto no = kumi::tuple {no_matching_shuffle, eve::index<-1>};
  // Coudn't figure out how to generalize well
  // only slide left for now
  // No masking 0s on avx512
  if constexpr( current_api < avx2 ) return no;
  else if constexpr( constexpr auto slide = idxm::is_slide_left(P::idxs) )
  {
    static_assert(G == 1, "verifying assumptions");
    constexpr auto alignr_p = idxm::slide_2_left_in_16_pattern<N::value>(P::g_size, *slide);

    wide<T, N> y = shuffle_l<2>(x, lane<16 / sizeof(T)>, pattern<1, na_>);

    return kumi::tuple {shuffle_l<2>(x, y, idxm::to_pattern<alignr_p>()), index<4>};
  }
  else return no;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l4_x86_shorts_lo_hi(p, g, x);
                matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l4_broadcast_lane_set_get(p, g, x);
                     matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l4_l5_x86_put_u64x2_in_position(p, g, x);
                     matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l4_l5_x86_slide_less_than_16(p, g, x);
                     matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_(EVE_SUPPORTS(avx512_), P p, fixed<G> g, logical<wide<T, N>> x)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l4_broadcast_lane_set_get(p, g, x);
                matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_x86_slide_less_than_16_x2(P, fixed<G>, wide<T, N> x, wide<T, N> y)
{
  constexpr auto no = kumi::tuple {no_matching_shuffle, eve::index<-1>};
  if constexpr ( P::reg_size != 32 || current_api < avx2 ) return no;
  else if constexpr( constexpr auto slide = idxm::is_slide_left_2(P::idxs, P::reg_size / P::g_size);
                     slide )
  {
    auto          ab  = x;
    auto          cd  = y;
    auto          bc  = shuffle_l<2>(x, y, eve::lane<16 / sizeof(T)>, eve::pattern<1, 2>);
    constexpr int n16 = 16 / sizeof(T);

    auto r = bc;

    if constexpr( slide > n16 )
    {
      constexpr auto alignr_p =
          idxm::slide_2_left_in_16_pattern<N::value>(P::g_size, *slide - n16);
      r = shuffle_l<2>(bc, cd, idxm::to_pattern<alignr_p>());
    }
    else
    {
      constexpr auto alignr_p = idxm::slide_2_left_in_16_pattern<N::value>(P::g_size, *slide);
      r                       = shuffle_l<2>(ab, bc, idxm::to_pattern<alignr_p>());
    }
    return kumi::tuple {r, eve::index<4>};
  }
  else return no;
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l4_l5_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x, wide<T, N> y)
requires(P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_l4_l5_x86_slide_less_than_16_x2(p, g, x, y);
                matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
