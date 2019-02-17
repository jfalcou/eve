//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef IS_EQUAL_HPP
#define IS_EQUAL_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/is_equal.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check is_equal behavior on homogeneous wide",
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
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::is_equal(Type(c - i), Type(i%2 ? i : c-i)); });
    TTS_SECTION("supports eve::is_equal") { TTS_EQUAL(ref, eve::is_equal(lhs, rhs)); }
    TTS_SECTION("supports operator == ") { TTS_EQUAL(ref, (lhs ==  rhs)); }
  }
}


#endif
