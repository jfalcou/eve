//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BITWISE_OR_HPP
#define BITWISE_OR_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/bitwise_or.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check bitwise_or behavior on homogeneous wide",
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
    wide<Type, T> lhs([](int i, int c) { return i; }), rhs([](int i, int) { return 2 * i; }),
        ref([](int i, int c) { return eve::bitwise_or(Type(i), Type(2 * i)); });

    TTS_SECTION("supports eve::bitwise_or") { TTS_EQUAL(ref, eve::bitwise_or(lhs, rhs)); }
    TTS_SECTION("supports operator|") { TTS_EQUAL(ref, lhs | rhs); }
  }
}

TTS_CASE_TPL("Check bitwise_or behavior on wide + scalar",
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
    wide<Type, T> lhs([](int i, int c) { return i % 3; }),
        ref([](int i, int c) { return eve::bitwise_or(Type(i % 3), Type(-1)); });

    TTS_SECTION("supports eve::bitwise_or") { TTS_EQUAL(ref, eve::bitwise_or(lhs, -1)); }
    TTS_SECTION("supports operator|") { TTS_EQUAL(ref, lhs | -1); }
  }
}

#endif
