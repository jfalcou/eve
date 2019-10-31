//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CSCH_HPP
#define CSCH_HPP

#include <eve/function/csch.hpp>
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
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <cmath>
#include <iomanip>

TTS_CASE("Check raw_(eve::csch) behavior")
{
  
  TTS_EXPR_IS ( eve::csch(Type(0)), Type);
  TTS_ULP_EQUAL(eve::csch(Type(1)), Type(eve::rec(std::sinh(1.0))), 0.5);
  TTS_ULP_EQUAL(eve::csch(Type(2)), Type(eve::rec(std::sinh(2.0))), 0.5);    
  TTS_ULP_EQUAL(eve::csch(Type(-2)),Type(eve::rec(std::sinh(-2.0))), 0.5);
  TTS_ULP_EQUAL(eve::csch(Type(-1)),Type(eve::rec(std::sinh(-1.0))), 0.5);
  TTS_IEEE_EQUAL(eve::csch(Type(0.0)), eve::Inf<Type>());
  TTS_IEEE_EQUAL(eve::csch(Type(-0.0)), eve::Minf<Type>());
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::csch(eve::Nan<Type>()), eve::Nan<Type>()); 
    TTS_IEEE_EQUAL(eve::csch(eve::Inf<Type>()), eve::Zero<Type>());
    TTS_IEEE_EQUAL(eve::csch(eve::Minf<Type>()), eve::Zero<Type>());
    TTS_EXPECT(eve::is_positive(eve::csch(eve::Inf<Type>())));
    TTS_EXPECT(eve::is_negative(eve::csch(eve::Minf<Type>())));
  }
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::csch(Type(i)), eve::rec(std::sinh(Type(i))), 0.5);
    TTS_ULP_EQUAL(eve::csch(-Type(i)), eve::rec(std::sinh(-Type(i))), 0.5); 
    TTS_ULP_EQUAL(eve::csch(1/Type(i)), eve::rec(std::sinh(1/Type(i))), 0.5);
    TTS_ULP_EQUAL(eve::csch(-1/Type(i)), eve::rec(std::sinh(1/Type(-i))), 0.5); 
  }
}

#endif
