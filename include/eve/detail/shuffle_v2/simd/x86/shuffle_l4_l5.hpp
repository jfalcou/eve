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
  else if constexpr( P::has_zeroes && current_api == avx2 ) return no;
  else if constexpr( !P::shuffle_16_first ) return no;
  else
  {
    constexpr auto shuffle16x2 = get<0>(*P::shuffle_16_first);
    constexpr auto within16    = get<1>(*P::shuffle_16_first);

    x            = shuffle_l<2>(x, eve::lane<16 / sizeof(T)>, idxm::to_pattern<shuffle16x2>());
    auto [x_, l] = shuffle_v2_core(x, eve::lane<G>, idxm::to_pattern<within16>());
    return kumi::tuple {x_, idxm::add_shuffle_levels(l, eve::index<2>)};
  }
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
  else if constexpr( auto r = shuffle_l4_broadcast_lane_set_get(p, g, x); matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_l4_l5_x86_put_u64x2_in_position(p, g, x);
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
 if constexpr( auto r = shuffle_l4_broadcast_lane_set_get(p, g, x); matched_shuffle<decltype(get<0>(r))> )
 {
  return r;
 }
 else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
