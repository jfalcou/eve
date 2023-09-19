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

template<typename P, typename T, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_x86_l6_l7_shift_shift_or(P, fixed<G>, T x)
{
  constexpr auto l_h = idxm::rotate_as_two_shifts_and_or(P::most_repeated);

  if constexpr( !l_h ) return kumi::tuple {no_matching_shuffle, eve::index<-1>};
  else
  {
    auto shift_l = shuffle_l<2>(x, idxm::to_pattern<l_h->at(0)>());
    auto shift_r = shuffle_l<2>(x, idxm::to_pattern<l_h->at(1)>());
    auto r       = shift_l | shift_r;
    return kumi::tuple {r, eve::index<6>};
  }
}

template<typename P, typename T, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_x86_l6_l7_u32_then_u16(P, fixed<G>, T x)
{
  constexpr auto no = kumi::tuple {no_matching_shuffle, eve::index<-1>};

  // this is only for sse2
  if constexpr( current_api >= ssse3 ) return no;
  else if constexpr( P::g_size != 2 || P::has_zeroes ) return no;
  else if constexpr( !P::shuffle_4_first ) return no;
  else
  {
    constexpr auto shuffle4x4 = get<0>(*P::shuffle_4_first);
    constexpr auto within4    = get<1>(*P::shuffle_4_first);

    x = shuffle_l<2>(x, eve::lane<4 / P::e_t_size>, idxm::to_pattern<shuffle4x4>());

    // this might be actually 2 and not 4 but should not be a problem, which'd lower
    // the total level but it's ok - we will still compute correctly
    auto [x_, l] = shuffle_v2_core(x, eve::lane<G>, idxm::to_pattern<within4>());
    return kumi::tuple {x_, idxm::add_shuffle_levels(l, eve::index<2>)};
  }
}

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l6_l7_(EVE_SUPPORTS(sse2_), P p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_128_> && (P::out_reg_size == P::reg_size)
{
  if constexpr( auto r = shuffle_x86_l6_l7_shift_shift_or(p, g, x);
                matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else if constexpr( auto r = shuffle_x86_l6_l7_u32_then_u16(p, g, x);
                     matched_shuffle<decltype(get<0>(r))> )
  {
    return r;
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
