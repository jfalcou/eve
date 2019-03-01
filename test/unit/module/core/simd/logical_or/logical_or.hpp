//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_OR_HPP
#define LOGICAL_OR_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/logical_or.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_or behavior on homogeneous wide",
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
    wide<Type, T> lhs([](int i, int c) { return c - i; }), rhs([](int i, int) { return i % 2; });
    wide<eve::logical<Type>, T> ref(
        [](int i, int c) { return eve::logical_or(Type(c - i), Type(i % 2)); });
    TTS_SECTION("supports eve::logical_or") { TTS_EQUAL(ref, eve::logical_or(lhs, rhs)); }
    TTS_SECTION("supports operator || ") { TTS_EQUAL(ref, (lhs || rhs)); }
  }
}

TTS_CASE_TPL("Check plus behavior on wide and scalar",
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
    wide<Type, T>               lhs([](auto i, auto) { return i; });
    wide<eve::logical<Type>, T> ref1([](int i, int) { return eve::logical_or(Type(i), Type(2)); });
    wide<eve::logical<Type>, T> ref2([](int i, int) { return eve::logical_or(Type(i), Type(0)); });
    TTS_SECTION("supports eve::logical_or") { TTS_EQUAL(ref1, eve::logical_or(lhs, Type(2))); }
    TTS_SECTION("supports eve::logical_or") { TTS_EQUAL(ref1, eve::logical_or(Type(2), lhs)); }
    TTS_SECTION("supports eve::logical_or") { TTS_EQUAL(ref2, eve::logical_or(lhs, Type(0))); }
    TTS_SECTION("supports eve::logical_or") { TTS_EQUAL(ref2, eve::logical_or(Type(0), lhs)); }

    TTS_SECTION("supports operator || ()") { TTS_EQUAL(ref1, lhs || 2); }
    TTS_SECTION("supports operator || ()") { TTS_EQUAL(ref1, Type(2) || lhs); }
    TTS_SECTION("supports operator || ()") { TTS_EQUAL(ref2, lhs || 0); }
    TTS_SECTION("supports operator || ()") { TTS_EQUAL(ref2, Type(0) || lhs); }
  }
}

TTS_CASE_TPL("Check logical_or behavior on homogeneous wide<logical>",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide;
  using eve::logical;

  TTS_SETUP("homogeneous wide<logical>")
  {
    wide<logical<Type>, T> lhs([](int i, int c) { return i%2 ==  0; }), rhs([](int i, int c) { return i%3 ==  0; });
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::logical_or(i%2 ==  0, i%3 ==  0); });
    TTS_SECTION("supports eve::logical_or") { TTS_EQUAL(ref, eve::logical_or(lhs, rhs)); }
    TTS_SECTION("supports operator && ") { TTS_EQUAL(ref, (lhs ||  rhs)); }
  }
}


TTS_CASE_TPL("Check logical_or behavior on wide<logical> and logical",
             fixed<1>,
             fixed<2>,
             fixed<4>,
             fixed<8>,
             fixed<16>,
             fixed<32>,
             fixed<64>
            )
{
  using eve::wide;
  using eve::logical;

  TTS_SETUP("wide<logical> and logical")
  {
    wide<logical<Type>, T> lhs([](int i, int c) { return i%2 ==  0; });
    logical<Type> rhs = true; 
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::logical_or(i%2 ==  0, true); });
    TTS_SECTION("supports eve::logical_or") { TTS_EQUAL(ref, eve::logical_or(lhs, rhs)); }
    TTS_SECTION("supports operator && ") { TTS_EQUAL(ref, (lhs ||  rhs)); }
  }
}

#endif
