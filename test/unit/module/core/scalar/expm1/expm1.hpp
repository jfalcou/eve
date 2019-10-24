//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXPM1_HPP
#define EXPM1_HPP

#include <eve/function/expm1.hpp>
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

TTS_CASE("Check eve::expm1 behavior")
{
  
  TTS_EXPR_IS ( eve::expm1(Type(0)), Type);
  TTS_ULP_EQUAL(eve::expm1(Type(1)), Type(std::expm1(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::expm1(Type(2)), Type(std::expm1(2.0)), 0.5);
  TTS_ULP_EQUAL(eve::expm1(Type(-2)),Type(std::expm1(-2.0)), 0.5);
  TTS_ULP_EQUAL(eve::expm1(Type(0)), Type(0), 0.5);
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::expm1(eve::Nan<Type>()), eve::Nan<Type>()); 
    TTS_IEEE_EQUAL(eve::expm1(eve::Inf<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(eve::expm1(eve::Minf<Type>()), Type(-1));
  }
  TTS_IEEE_EQUAL(eve::expm1(eve::Maxlog<Type>()), eve::Inf<Type>());
  TTS_IEEE_EQUAL(eve::expm1(eve::Minlog<Type>()),Type(-1));
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::expm1(Type(i)), std::expm1(Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::expm1(-Type(i)), std::expm1(-Type(i)), 0.5); 
  }
}

#endif
