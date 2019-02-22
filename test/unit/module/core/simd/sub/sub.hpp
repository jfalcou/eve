//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef MINUS_HPP
#define MINUS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/sub.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check sub behavior on wide",
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
    wide<Type, T> lhs([](int i, int c) { return c + i; }), rhs([](int i, int) { return i; }),
        ref(T::value);

    TTS_SECTION("supports eve::sub") { TTS_EQUAL(ref, eve::sub(lhs, rhs)); }

    TTS_SECTION("supports operator-()") { TTS_EQUAL(ref, lhs - rhs); }
  }
}

TTS_CASE_TPL("Check plus behavior on wide",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>)
{
  using eve::wide;

  TTS_SETUP("A correctly initialized wide and a scalar")
  {
    wide<Type, T> lhs([](auto i, auto) { return i; })
      , ref1([](auto i, auto) { return i-Type(4); })
      , ref2([](auto i, auto) { return   Type(4)-i;}); 
    
    TTS_SECTION("supports eve::sub") { TTS_EQUAL(ref1, eve::sub(lhs, 4)); }
    TTS_SECTION("supports eve::sub") { TTS_EQUAL(ref2, eve::sub(4, lhs)); }
    
    TTS_SECTION("supports operator-()") { TTS_EQUAL(ref1, lhs - 4); }
    TTS_SECTION("supports operator-()") { TTS_EQUAL(ref2, 4- lhs); }
  }
}

#endif
