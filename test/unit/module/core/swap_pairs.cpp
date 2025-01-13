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
              tts::generate(tts::randoms(eve::valmin, eve::valmax))
             )
<typename T>(T const& a0)
{
  using eve::swap_pairs;
  constexpr size_t S =  eve::cardinal_v<T> - 1;
  constexpr auto _0 = eve::index_t<0>();
  constexpr auto _S = eve::index_t<S>();
  constexpr auto _H = eve::index_t<S/2>();

  T refS = [&](auto i, auto) { return i == 0 ? a0.get(S) : (i == S ? a0.get(0) : a0.get(i)); };
  T refH = [&](auto i, auto) { return i == 0 ? a0.get(S/2) : (i == S/2 ? a0.get(0) : a0.get(i)); };

  TTS_EQUAL(swap_pairs(a0, _0, _S), refS);
  TTS_EQUAL(swap_pairs(a0, _0, _H), refH);
};
