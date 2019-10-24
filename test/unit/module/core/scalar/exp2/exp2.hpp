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
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/maxlog2.hpp>
#include <eve/constant/minlog2.hpp>
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
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(eve::exp2(eve::Nan<Type>()), eve::Nan<Type>()); 
      TTS_IEEE_EQUAL(eve::exp2(eve::Inf<Type>()), eve::Inf<Type>());
      TTS_IEEE_EQUAL(eve::exp2(eve::Minf<Type>()), eve::Zero<Type>());
    }
    TTS_IEEE_EQUAL(eve::exp2(eve::Maxlog<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(eve::exp2(eve::Minlog<Type>()), eve::Zero<Type>());
    
    for(int i=1; i < eve::Maxlog2<Type>(); i *= 3)
    {
      TTS_ULP_EQUAL(eve::exp2(Type(i)), std::exp2(Type(i)), 0.5);
      TTS_ULP_EQUAL(eve::exp2(-Type(i)), std::exp2(-Type(i)), 0.5); 
    }
  }
  else 
  {
    for(unsigned int i=0; i < eve::Maxlog2<Type>(); ++i)
    {
      TTS_EQUAL(eve::exp2(Type(i)), Type(std::pow(2, Type(i))));
    }
  }
}

#endif
