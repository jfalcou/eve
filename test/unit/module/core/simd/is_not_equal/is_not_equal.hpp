//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_NOT_EQUAL_HPP
#define IS_NOT_EQUAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_not_equal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_not_equal behavior on homogeneous wide",
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
    using t_t = wide<Type, T>;
    using l_t = eve::as_logical_t <t_t>; 
    t_t lhs([](int i, int c) { return c - i; }), rhs([](int i, int c) { return i%2 ? i : c-i; });
    l_t  ref([](int i, int c) { return eve::is_not_equal(Type(c - i), Type(i%2 ? i : c-i)); });
    TTS_SECTION("supports eve::is_not_equal") { TTS_EQUAL(ref, eve::is_not_equal(lhs, rhs)); }
    TTS_SECTION("supports operator == ") { TTS_EQUAL(ref, (lhs !=  rhs)); }
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
    using t_t = wide<Type, T>;
    using l_t = eve::as_logical_t <t_t>; 
    t_t  lhs([](auto i, auto) { return i; });
    l_t ref([](int i, int c) { return eve::is_not_equal(Type(i), Type(2)); });

    TTS_SECTION("supports eve::is_not_equal") { TTS_EQUAL(ref, eve::is_not_equal(lhs, Type(2))); }
    TTS_SECTION("supports eve::is_not_equal") { TTS_EQUAL(ref, eve::is_not_equal(Type(2), lhs)); }

    TTS_SECTION("supports operator != ()") { TTS_EQUAL(ref, lhs != 2); }
    TTS_SECTION("supports operator != ()") { TTS_EQUAL(ref, 2 != lhs); }
  }
}

TTS_CASE_TPL("Check is_not_equal behavior on homogeneous wide<logical>",
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
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_not_equal(i%2 == 0, i%3 == 0); });
    TTS_SECTION("supports eve::is_not_equal") { TTS_EQUAL(ref, eve::is_not_equal(lhs, rhs)); }
    TTS_SECTION("supports operator != ") { TTS_EQUAL(ref, (lhs !=  rhs)); }
  }
}
#endif
