//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_LESSGREATER_HPP
#define IS_LESSGREATER_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_lessgreater.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_lessgreater behavior on homogeneous wide",
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

  TTS_SETUP("A correctly initialized wide")
  {
    wide<Type, T> lhs([](int i, int c) { return c - i; }), rhs([](int i, int c) { return i%2 ? i : c-i; });
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_lessgreater(Type(c - i), Type(i%2 ? i : c-i)); });
    TTS_SECTION("supports eve::is_lessgreater") { TTS_EQUAL(ref, eve::is_lessgreater(lhs, rhs)); }
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
    wide<eve::logical<Type>, T> ref([](int i, int) { return eve::is_lessgreater(Type(i), Type(2)); });
    TTS_SECTION("supports eve::is_lessgreater") { TTS_EQUAL(ref, eve::is_lessgreater(lhs, Type(2))); }
    TTS_SECTION("supports eve::is_lessgreater") { TTS_EQUAL(ref, eve::is_lessgreater(Type(2), lhs)); }
  }
}

TTS_CASE_TPL("Check is_lessgreater behavior on homogeneous wide<logical>",
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

  TTS_SETUP("A correctly initialized wide")
  {
    wide<logical<Type>, T> lhs([](int i, int c) { return i%2 == 0; }), rhs([](int i, int c) { return i%3 == 0; });
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_lessgreater(i%2 == 0, i%3 == 0); });
    TTS_SECTION("supports eve::is_lessgreater") { TTS_EQUAL(ref, eve::is_lessgreater(lhs, rhs)); }
  }
}

#endif
