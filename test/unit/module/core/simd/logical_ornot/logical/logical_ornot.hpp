//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry Lapreste

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef LOGICAL_ORNOT_HPP
#define LOGICAL_ORNOT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/logical_ornot.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check logical_ornot behavior on homogeneous wide<logical>",
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

  TTS_SETUP(" homogeneous wide<logical>")
  {
    wide<logical<Type>, T> lhs([](int i, int c) { return i%2 ==  0; }), rhs([](int i, int c) { return i%3 ==  0; });
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::logical_ornot(i%2 ==  0, i%3 ==  0); });
    TTS_SECTION("supports eve::logical_ornot") { TTS_EQUAL(ref, eve::logical_ornot(lhs, rhs)); }
  }
}

TTS_CASE_TPL("Check logical_ornot behavior on wide<logical> and logical",
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
    wide < eve::logical < Type>, T >  ref([](int i, int c) { return eve::logical_ornot(i%2 ==  0, true); });
    TTS_SECTION("supports eve::logical_ornot") { TTS_EQUAL(ref, eve::logical_ornot(lhs, rhs)); }
  }
}

#endif
