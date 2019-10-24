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
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/minlog.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check raw_(eve::exp) behavior")
{
  
  TTS_EXPR_IS ( eve::exp(Type(0)), Type);
  TTS_ULP_EQUAL(eve::exp(Type(1)), Type(std::exp(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::exp(Type(2)), Type(std::exp(2.0)), 0.5);    
  TTS_ULP_EQUAL(eve::exp(Type(-2)),Type(std::exp(-2.0)), 0.5);
  TTS_ULP_EQUAL(eve::exp(Type(0)), Type(1), 0.5);
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::exp(eve::Nan<Type>()), eve::Nan<Type>()); 
    TTS_IEEE_EQUAL(eve::exp(eve::Inf<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(eve::exp(eve::Minf<Type>()), eve::Zero<Type>());
  }
  TTS_IEEE_EQUAL(eve::exp(eve::Maxlog<Type>()), eve::Inf<Type>());
  TTS_IEEE_EQUAL(eve::exp(eve::Minlog<Type>()), eve::Zero<Type>());
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::exp(Type(i)), std::exp(Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::exp(-Type(i)), std::exp(-Type(i)), 0.5); 
  }
}

#endif
