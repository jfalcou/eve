//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_GREATER_HPP
#define IS_GREATER_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_greater.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_greater behavior on homogeneous wide",
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
    wide<Type, T> lhs([](int i, int c) { return c - i; }),
        rhs([](int i, int c) { return i % 2 ? i : c - i; });
    wide<eve::logical<Type>, T> ref(
        [](int i, int c) { return eve::is_greater(Type(c - i), Type(i % 2 ? i : c - i)); });
    TTS_SECTION("supports eve::is_greater") { TTS_EQUAL(ref, eve::is_greater(lhs, rhs)); }
    TTS_SECTION("supports operator >  ") { TTS_EQUAL(ref, (lhs > rhs)); }
  }
}

TTS_CASE_TPL("Check is_greater behavior on wide and scalar",
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
    wide<Type, T>               lhs([](int i, int c) { return c - i; });
    wide<eve::logical<Type>, T> ref1(
        [](int i, int c) { return eve::is_greater(Type(c - i), Type(1)); });
    wide<eve::logical<Type>, T> ref2(
        [](int i, int c) { return eve::is_greater(Type(1), Type(c - i)); });
    TTS_SECTION("supports eve::is_greater1") { TTS_EQUAL(ref1, eve::is_greater(lhs, Type(1))); }
    TTS_SECTION("supports eve::is_greater2") { TTS_EQUAL(ref2, eve::is_greater(Type(1), lhs)); }

    TTS_SECTION("1 supports operator < ") { TTS_EQUAL(ref1, (lhs > Type(1))); }
    TTS_SECTION("2 supports operator < ") { TTS_EQUAL(ref2, (Type(1) > lhs)); }
  }
}
#endif
