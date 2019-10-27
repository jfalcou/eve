//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TANH_HPP
#define TANH_HPP

#include <eve/function/tanh.hpp>
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
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/log_2.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check eve::tanh behavior")
{
  
  TTS_EXPR_IS ( eve::tanh(Type(0)), Type);
  TTS_ULP_EQUAL(eve::tanh(Type(1)), Type(std::tanh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::tanh(Type(2)), Type(std::tanh(2.0)), 0.5);    
  TTS_ULP_EQUAL(eve::tanh(Type(-2)),Type(std::tanh(-2.0)), 0.5);
  TTS_ULP_EQUAL(eve::tanh(Type(-1)),Type(std::tanh(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::tanh(Type(0)), Type(0));
  TTS_ULP_EQUAL(eve::tanh(eve::Maxlog<Type>()),Type(std::tanh(eve::Maxlog<Type>())), 0.5);
  TTS_ULP_EQUAL(eve::tanh(eve::Mindenormal<Type>()),Type(std::tanh(eve::Mindenormal<Type>())), 0.5); 
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::tanh(eve::Nan<Type>()), eve::Nan<Type>()); 
    TTS_IEEE_EQUAL(eve::tanh(eve::Inf<Type>()), Type(1));
    TTS_IEEE_EQUAL(eve::tanh(eve::Minf<Type>()), Type(-1));
  }
  
  for(Type i=1; i < eve::Maxlog<Type>(); i*= 1.923)
  {
    TTS_ULP_EQUAL(eve::tanh(Type(i)), std::tanh(Type(i)), 1.0);
    TTS_ULP_EQUAL(eve::tanh(-Type(i)), std::tanh(-Type(i)), 1.0); 
    TTS_ULP_EQUAL(eve::tanh(1/Type(i)), std::tanh(1/Type(i)), 1.0);
    TTS_ULP_EQUAL(eve::tanh(-1/Type(i)), std::tanh(-1/Type(i)), 1.0); 
  }
}

#endif
