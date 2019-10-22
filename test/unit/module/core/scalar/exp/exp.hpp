//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXP_HPP
#define EXP_HPP

#include <eve/function/exp.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check raw_(eve::exp) behavior")
{
  
  TTS_EXPR_IS ( eve::exp(Type(0)), Type);
  TTS_ULP_EQUAL(eve::exp(Type(1)), Type(std::exp(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::exp(Type(2)), Type(std::exp(2.0)), 0.5);    
  TTS_ULP_EQUAL(eve::exp(Type(-2)),Type(std::exp(-2.0)), 0.5);
  TTS_ULP_EQUAL(eve::exp(Type(0)), Type(1), 0.5);
  
  for(int i=1; i < 70; i *= 3)
  {
    TTS_ULP_EQUAL(eve::exp(Type(i)), std::exp(Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::exp(-Type(i)), std::exp(-Type(i)), 0.5); 
  }
}

#endif
