//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef INCREMENT_HPP
#define INCREMENT_HPP

#include "test.hpp"
#include <eve/wide.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::as_aligned;
using eve::fixed;

// Generator for the base values
auto baseg = [](auto i, auto) { return i; };
auto nextg = [](auto i, auto) { return i + 1; };

TTS_CASE_TPL("Check self-increment on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  TTS_WHEN("A value is initialized")
  {
    wide<EVE_TYPE, T> simd(baseg), next(nextg);
    wide<EVE_TYPE, T> prev(simd), res;

    TTS_AND_THEN("We call post-increment operator on the value")
    {
      res = simd++;
      TTS_EXPECT(std::equal(simd.begin(), simd.end(), next.begin()));
      TTS_EXPECT(std::equal(res.begin(), res.end(), prev.begin()));
    }

    TTS_AND_THEN("We call pre-increment operator on the value")
    {
      res = ++simd;
      TTS_EXPECT(std::equal(simd.begin(), simd.end(), next.begin()));
      TTS_EXPECT(std::equal(res.begin(), res.end(), next.begin()));
    }
  }
}

#endif
