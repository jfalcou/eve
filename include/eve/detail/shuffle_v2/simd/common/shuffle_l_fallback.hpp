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

  // to mask and from mask + 2 each
  return kumi::tuple {to_logical(shuffled), eve::index<decltype(l)::value + 4>};
}
}
