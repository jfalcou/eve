//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include <eve/wide.hpp>
#include <eve/logical.hpp>
#include <tts/tests/basic.hpp>
#include <algorithm>

using eve::fixed;

TTS_CASE_TPL("Check enumerating constructor for wide of logical",
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

  auto filler = [](auto i, auto) { return i % 3 ? true : false; };

  logical<wide<EVE_TYPE, T>>              simd(filler);
  std::array<logical<EVE_TYPE>, T::value> ref;
  for(std::size_t i = 0; i < T::value; ++i) ref[ i ] = filler(i, T::value);

  TTS_EXPECT(std::equal(simd.begin(), simd.end(), ref.begin()));
}
