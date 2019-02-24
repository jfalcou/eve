//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_MASK_HPP
#define BITWISE_MASK_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/function/simd/bitwise_mask.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check bitwise_mask behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  TTS_SETUP("A correctly initialized wide")
  {
    wide<Type, T> lhs([](int i, int) { return i%2; }),
        ref([](int i, int) { return eve::bitwise_mask(Type(i%2)); });

    TTS_SECTION("supports eve::bitwise_mask")
    {
      if constexpr(std::is_integral_v<Type>)
        TTS_EQUAL(ref, eve::bitwise_mask(lhs));
      else
        TTS_IEEE_EQUAL(ref, eve::bitwise_mask(lhs));
    }
  }
}

#endif
