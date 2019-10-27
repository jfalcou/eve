//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COTH_HPP
#define COTH_HPP

#include <eve/function/coth.hpp>
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
#include <eve/function/rec.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check eve::coth behavior")
{
  
  TTS_EXPR_IS ( eve::coth(Type(0)), Type);
  TTS_ULP_EQUAL(eve::coth(Type(1)), Type(eve::rec(std::tanh(1.0))), 0.5);
  TTS_ULP_EQUAL(eve::coth(Type(2)), Type(eve::rec(std::tanh(2.0))), 0.5);    
  TTS_ULP_EQUAL(eve::coth(Type(-2)),Type(eve::rec(std::tanh(-2.0))), 0.5);
  TTS_ULP_EQUAL(eve::coth(Type(-1)),Type(eve::rec(std::tanh(-1.0))), 0.5);
  TTS_IEEE_EQUAL(eve::coth(Type(0.0)), eve::Inf<Type>());
  TTS_IEEE_EQUAL(eve::coth(Type(-0.0)), eve::Minf<Type>());    
  TTS_ULP_EQUAL(eve::coth(eve::Maxlog<Type>()),Type(eve::rec(std::tanh(eve::Maxlog<Type>()))), 0.5);
  TTS_ULP_EQUAL(eve::coth(eve::Mindenormal<Type>()),Type(eve::rec(std::tanh(eve::Mindenormal<Type>()))), 0.5); 
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::coth(eve::Nan<Type>()), eve::Nan<Type>()); 
    TTS_IEEE_EQUAL(eve::coth(eve::Inf<Type>()), Type(1));
    TTS_IEEE_EQUAL(eve::coth(eve::Minf<Type>()), Type(-1));
  }
  
  for(Type i=1; i < eve::Maxlog<Type>(); i*= 1.923)
  {
    TTS_ULP_EQUAL(eve::coth(Type(i)), eve::rec(std::tanh(Type(i))), 1.0);
    TTS_ULP_EQUAL(eve::coth(-Type(i)), eve::rec(std::tanh(-Type(i))), 1.0); 
    TTS_ULP_EQUAL(eve::coth(1/Type(i)), eve::rec(std::tanh(1/Type(i))), 1.0);
    TTS_ULP_EQUAL(eve::coth(-1/Type(i)), eve::rec(std::tanh(-1/Type(i))), 1.0); 
  }
}

#endif
