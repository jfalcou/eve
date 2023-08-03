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

template<typename P, arithmetic_scalar_value T, typename N, std::ptrdiff_t G>
EVE_FORCEINLINE auto
shuffle_l_fallback_(EVE_SUPPORTS(avx_), P p, fixed<G> g, wide<T, N> x)
requires std::same_as<abi_t<T, N>, x86_256_> && (P::out_reg_size == P::reg_size)
         && (P::g_size <= 2) && (current_api == avx)
{
  auto lo_hi     = x.slice();
  auto p_lo_p_hi = idxm::slice_pattern<N() / 2>(p);

  auto lo = get<0>(lo_hi);
  auto hi = get<1>(lo_hi);
  auto p_lo = get<0>(p_lo_p_hi);
  auto p_hi = get<1>(p_lo_p_hi);

  if constexpr(
      requires { shuffle_v2_core(lo, hi, g, p_lo); }
      && requires { shuffle_v2_core(lo, hi, g, p_hi); } )
  {
    auto [shuffled_lo, lo_l] = shuffle_v2_core(lo, hi, g, p_lo);
    auto [shuffled_hi, hi_l] = shuffle_v2_core(lo, hi, g, p_hi);

    x = wide<T, N> {shuffled_lo, shuffled_hi};

    auto l = eve::index<decltype(lo_l)::value + decltype(hi_l)::value + 4>;

    return kumi::tuple {x, l};
  }
  else return kumi::tuple {no_matching_shuffle, eve::index<-1>};
}

}
