//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SPLAT_HPP
#define SPLAT_HPP

#include "test.hpp"
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;

TTS_CASE_TPL("Check splatting constructor for wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  Type          base = 42;
  wide<Type, T> simd(base);

  TTS_EXPECT(std::all_of(simd.begin(), simd.end(), [=](auto e) { return e == base; }));
}

TTS_CASE_TPL("Check splatting constructor for wide<logical>",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::logical;
  using eve::wide;

  {
    wide<logical<Type>, T> simd(true);
    TTS_EXPECT(std::all_of(simd.begin(), simd.end(), [](auto e) { return e == true; }));
  }

  {
    wide<logical<Type>, T> simd(false);
    TTS_EXPECT(std::all_of(simd.begin(), simd.end(), [](auto e) { return e == false; }));
  }
}

#endif
