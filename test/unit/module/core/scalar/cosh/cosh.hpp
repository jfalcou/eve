//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef COSH_HPP
#define COSH_HPP

#include <eve/function/cosh.hpp>
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
#include <eve/constant/log_2.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check raw_(eve::cosh) behavior")
{
  
  TTS_EXPR_IS ( eve::cosh(Type(0)), Type);
  TTS_ULP_EQUAL(eve::cosh(Type(1)), Type(std::cosh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::cosh(Type(2)), Type(std::cosh(2.0)), 0.5);    
  TTS_ULP_EQUAL(eve::cosh(Type(-2)),Type(std::cosh(-2.0)), 0.5);
  TTS_ULP_EQUAL(eve::cosh(Type(-1)),Type(std::cosh(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::cosh(Type(0)), Type(1));
  TTS_ULP_EQUAL(eve::cosh(eve::Maxlog<Type>()),Type(std::cosh(eve::Maxlog<Type>())), 0.5);
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::cosh(eve::Nan<Type>()), eve::Nan<Type>()); 
    TTS_IEEE_EQUAL(eve::cosh(eve::Inf<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(eve::cosh(eve::Minf<Type>()), eve::Inf<Type>());
  }
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::cosh(Type(i)), std::cosh(Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::cosh(-Type(i)), std::cosh(-Type(i)), 0.5); 
    TTS_ULP_EQUAL(eve::cosh(1/Type(i)), std::cosh(1/Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::cosh(-1/Type(i)), std::cosh(1/Type(-i)), 0.5); 
  }
}

#endif
