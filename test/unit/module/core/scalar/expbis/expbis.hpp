//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXPBIS_HPP
#define EXPBIS_HPP

#include <eve/function/expbis.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check raw_(eve::expbis) behavior")
{
  
  TTS_EXPR_IS ( eve::expbis(Type(0)), Type);
  TTS_ULP_EQUAL(eve::expbis(Type(1)), Type(std::exp(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::expbis(Type(2)), Type(std::exp(2.0)), 0.5);    
  TTS_ULP_EQUAL(eve::expbis(Type(-2)),Type(std::exp(-2.0)), 0.5);
  TTS_ULP_EQUAL(eve::expbis(Type(0)), Type(1), 0.5);
  
  for(int i=1; i < 70; i *= 3)
  {
    TTS_ULP_EQUAL(eve::expbis(Type(i)), std::exp(Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::expbis(-Type(i)), std::exp(-Type(i)), 0.5); 
  }
}

#endif
