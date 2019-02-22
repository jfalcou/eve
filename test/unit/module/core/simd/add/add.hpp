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
#include <eve/function/simd/add.hpp>
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
    wide<Type, T> lhs([](auto i, auto) { return i; }), rhs([](auto i, auto c) { return c - i; }),
        ref(T::value);

    TTS_SECTION("supports eve::add") { TTS_EQUAL(ref, eve::add(lhs, rhs)); }

    TTS_SECTION("supports operator+()") { TTS_EQUAL(ref, lhs + rhs); }
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
    wide<Type, T> lhs([](auto i, auto) { return i; }),
        ref([](auto i, auto) { return i + Type(4); });

    TTS_SECTION("supports eve::add") { TTS_EQUAL(ref, eve::add(lhs, 4)); }
    TTS_SECTION("supports eve::add") { TTS_EQUAL(ref, eve::add(4, lhs)); }

    TTS_SECTION("supports operator+()") { TTS_EQUAL(ref, lhs + 4); }
    TTS_SECTION("supports operator+()") { TTS_EQUAL(ref, 4 + lhs); }
  }
}

#endif
