//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef PLUS_HPP
#define PLUS_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/div.hpp>
#include <eve/wide.hpp>

using eve::fixed;

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

  TTS_SETUP("two correctly initialized wide")
  {
    wide<Type, T> lhs([](auto i, auto) { return i+1; }), rhs([](auto i, auto c) { return c - i+1; }),
      ref([](auto i, auto c) { return Type(i+1)/Type((c - i+1)); });

    std::cout << "lhs " << lhs << std::endl;
    std::cout << "rhs " << rhs << std::endl;
    std::cout << "div " << eve::div(lhs, rhs)<< std::endl;
    TTS_SECTION("supports eve::div") { TTS_EQUAL(ref, eve::div(lhs, rhs)); }

    TTS_SECTION("supports operator/()") { TTS_EQUAL(ref, lhs / rhs); }
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
    wide<Type, T> lhs([](auto i, auto) { return i+1; }),
      ref1([](auto i, auto) { return (i+1) /Type(4); }),
      ref2([](auto i, auto) { return Type(4)/(i+1); });

    TTS_SECTION("supports eve::div") { TTS_EQUAL(ref1, eve::div(lhs, 4)); }
    TTS_SECTION("supports eve::div") { TTS_EQUAL(ref2, eve::div(4, lhs)); }

    TTS_SECTION("supports operator/()") { TTS_EQUAL(ref1, lhs / 4); }
    TTS_SECTION("supports operator/()") { TTS_EQUAL(ref2, 4 / lhs); }
  }
}

#endif
