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

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l_fallback_(EVE_SUPPORTS(cpu_), pattern_t<I...> p, fixed<G> g, logical<wide<T, N>> x)
requires(!abi_t<T, N>::is_wide_logical) && requires { shuffle_v2_core(x.bits(), g, p); }
{
  auto [shuffled, l] = shuffle_v2_core(x.bits(), g, p);

  // converting from logical to bits and back - costs 2 levels each.
  return kumi::tuple {to_logical(shuffled), eve::index<decltype(l)::value + 4>};
}

template<arithmetic_scalar_value T, typename N, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l_fallback_(EVE_SUPPORTS(cpu_), pattern_t<I...> p, fixed<G> g, logical<wide<T, N>> x,  logical<wide<T, N>> y)
requires(!abi_t<T, N>::is_wide_logical) && requires { shuffle_v2_core(x.bits(), y.bits(), g, p); }
{
  auto [shuffled, l] = shuffle_v2_core(x.bits(), y.bits(), g, p);

  // 2 convertions from logical to bits and 1 back - costs 6 levels.
  return kumi::tuple {to_logical(shuffled), eve::index<decltype(l)::value + 6>};
}


template<simd_value T, std::ptrdiff_t G, std::ptrdiff_t... I>
EVE_FORCEINLINE auto
shuffle_l_fallback_(EVE_SUPPORTS(cpu_), pattern_t<I...> p, fixed<G> g, T x, T y)
{
  // sse2 has no blend. Other should try blend/no blend options.
  if constexpr ( eve::current_api < eve::sse4_1 )
  {
    return shuffle_2_using_or(p, g, x, y);
  }
  else return kumi::tuple{no_matching_shuffle, eve::index<-1>};
}

}
