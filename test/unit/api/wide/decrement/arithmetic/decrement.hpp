//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef DECREMENT_HPP
#define DECREMENT_HPP

#include "test.hpp"
#include <eve/wide.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::as_aligned;
using eve::fixed;

// Generator for the base values
auto baseg = [](auto i, auto) { return i + 1; };
auto nextg = [](auto i, auto) { return i; };

TTS_CASE_TPL("Check self-decrement on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  wide<Type, T> simd(baseg), next(nextg);
  wide<Type, T> prev(baseg), res;

  TTS_SUBCASE("support for operator--()")
  {
    res = simd--;
    TTS_EXPECT(std::equal(simd.begin(), simd.end(), next.begin()));
    TTS_EXPECT(std::equal(res.begin(), res.end(), prev.begin()));
  }

  TTS_SUBCASE("support for operator--(int)")
  {
    res = --simd;
    TTS_EXPECT(std::equal(simd.begin(), simd.end(), next.begin()));
    TTS_EXPECT(std::equal(res.begin(), res.end(), next.begin()));
  }
}

#endif
