//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CBRT_HPP
#define CBRT_HPP

#include <eve/function/cbrt.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check raw_(eve::cbrt) behavior")
{

  TTS_EXPR_IS ( eve::cbrt(Type(0)), Type);
  
  TTS_ULP_EQUAL(eve::cbrt(Type(1)), Type(1), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(Type(8)), Type(2), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(Type(27)), Type(3), 0.5);
  TTS_ULP_EQUAL(eve::cbrt(Type(0)), Type(0), 0.5);
  
 for(int i=1; i < 10000; i *= 3)
 {
   TTS_ULP_EQUAL(eve::cbrt(Type(i)), std::cbrt(Type(i)), 0.5);
 }
}

#endif
