//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXTRACT_HPP
#define EXTRACT_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/extract.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check extract behavior on wide + scalar",
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
    wide<Type, T> lhs([](int i, int ) { return i+ 3; });

    TTS_SECTION("supports eve::extract") { TTS_EQUAL(Type(T::value+2), eve::extract(lhs, T::value-1)); }
    TTS_SECTION("supports static eve::extract") { TTS_EQUAL(Type(T::value+2), eve::extract(lhs, std::integral_constant<int, T::value-1>())); }
  }
}

#endif
