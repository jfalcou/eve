//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SINH_HPP
#define SINH_HPP

#include <eve/function/sinh.hpp>
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

TTS_CASE("Check raw_(eve::sinh) behavior")
{
  
  TTS_EXPR_IS ( eve::sinh(Type(0)), Type);
  TTS_ULP_EQUAL(eve::sinh(Type(1)), Type(std::sinh(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::sinh(Type(2)), Type(std::sinh(2.0)), 0.5);    
  TTS_ULP_EQUAL(eve::sinh(Type(-2)),Type(std::sinh(-2.0)), 0.5);
  TTS_ULP_EQUAL(eve::sinh(Type(-1)),Type(std::sinh(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::sinh(Type(0)), Type(0));
  TTS_EXPECT(eve::is_positive(eve::sinh(Type(0.0))));
  TTS_EXPECT(eve::is_negative(eve::sinh(Type(-0.0))));
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::sinh(eve::Nan<Type>()), eve::Nan<Type>()); 
    TTS_IEEE_EQUAL(eve::sinh(eve::Inf<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(eve::sinh(eve::Minf<Type>()), eve::Minf<Type>());
  }
  
  for(int i=1; i < eve::Maxlog<Type>(); i *= 3)
  {
    TTS_ULP_EQUAL(eve::sinh(Type(i)), std::sinh(Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::sinh(-Type(i)), std::sinh(-Type(i)), 0.5); 
    TTS_ULP_EQUAL(eve::sinh(1/Type(i)), std::sinh(1/Type(i)), 0.5);
    TTS_ULP_EQUAL(eve::sinh(-1/Type(i)), std::sinh(1/Type(-i)), 0.5); 
  }
}

#endif
