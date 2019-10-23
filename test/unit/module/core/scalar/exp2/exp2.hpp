//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXP2_HPP
#define EXP2_HPP

#include <eve/function/exp2.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check raw_(eve::exp2) behavior")
{
  
  TTS_EXPR_IS ( eve::exp2(Type(0)), Type);
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_ULP_EQUAL(eve::exp2(Type(1)), Type(std::exp2(1.0)), 0.5);
    TTS_ULP_EQUAL(eve::exp2(Type(2)), Type(std::exp2(2.0)), 0.5);
    TTS_ULP_EQUAL(eve::exp2(Type(-2)),Type(std::exp2(-2.0)), 0.5);
    TTS_ULP_EQUAL(eve::exp2(Type(0)), Type(1), 0.5);
    
    for(int i=1; i < 70; i *= 3)
    {
      TTS_ULP_EQUAL(eve::exp2(Type(i)), std::exp2(Type(i)), 0.5);
      TTS_ULP_EQUAL(eve::exp2(-Type(i)), std::exp2(-Type(i)), 0.5); 
    }
  }
  else if constexpr(std::is_signed_v<Type>)
  {
    for(unsigned int i=0; i < sizeof(Type)*8-1; ++i)
    {
      TTS_ULP_EQUAL(eve::exp2(Type(i)), Type(std::pow(2, Type(i))), 0.5);
    }
  }
  else
  {
    for(unsigned int i=0; i < sizeof(Type)*8; ++i)
    {
      TTS_EQUAL(eve::exp2(Type(i)), Type(std::exp2(Type(i))));
    }
  }
}

#endif
