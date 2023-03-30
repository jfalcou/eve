/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//  swap_pairs simd tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of swap_pairs(simd) on all types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)
                           )
             )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  using eve::swap_pairs;
  using eve::detail::map;
  constexpr size_t S =  eve::cardinal_v<v_t>-1;
  constexpr auto _0 = std::integral_constant<size_t, 0>();
  constexpr auto _S = std::integral_constant<size_t, S>();
  constexpr auto _H = std::integral_constant<size_t, S/2>();
  TTS_EQUAL(swap_pairs(a0, _0, _S), map([_0, _S](auto e) -> v_t { return swap_pairs(e, _0, _S); }, a0));
  TTS_EQUAL(swap_pairs(a0, _0, _H), map([_0, _H](auto e) -> v_t { return swap_pairs(e, _0, _H); }, a0));
};
