//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SPLAT_HPP
#define SPLAT_HPP

#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <eve/wide.hpp>
#include <algorithm>

using eve::fixed;

TTS_CASE_TPL("Check splatting constructor for arithmetic wide",
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

#endif
