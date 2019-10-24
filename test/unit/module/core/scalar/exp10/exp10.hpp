//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EXP10_HPP
#define EXP10_HPP

#include <eve/function/exp10.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/maxlog10.hpp>
#include <eve/constant/minlog10.hpp>
#include <type_traits>
#include <cmath>
#include <iomanip>

TTS_CASE("Check eve::exp10 behavior")
{
  TTS_EXPR_IS ( eve::exp10(Type(0)), Type);
  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_ULP_EQUAL(eve::exp10(Type(1)), Type(10), 0.5);
    TTS_ULP_EQUAL(eve::exp10(Type(2)), Type(100), 0.5);
    TTS_ULP_EQUAL(eve::exp10(Type(-2)),Type(1)/100, 0.5);
    TTS_ULP_EQUAL(eve::exp10(Type(0)), Type(1), 0.5);
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_IEEE_EQUAL(eve::exp10(eve::Nan<Type>()), eve::Nan<Type>()); 
      TTS_IEEE_EQUAL(eve::exp10(eve::Inf<Type>()), eve::Inf<Type>());
      TTS_IEEE_EQUAL(eve::exp10(eve::Minf<Type>()), eve::Zero<Type>());
    }
    TTS_IEEE_EQUAL(eve::exp10(eve::Maxlog10<Type>()), eve::Inf<Type>());
    TTS_IEEE_EQUAL(eve::exp10(eve::Minlog10<Type>()), eve::Zero<Type>());
     
    for(int i=1; i <  eve::Maxlog10<Type>(); i *= 3)
    {
      TTS_ULP_EQUAL(eve::exp10(Type(i)), Type(std::pow(10, Type(i))), 0.5);
      TTS_ULP_EQUAL(eve::exp10(-Type(i)),Type(std::pow(10, -Type(i))), 0.5);
    }
  }
  else
  {
    for(Type i=0; i <  eve::Maxlog10<Type>(); ++i)
    {
      TTS_EQUAL(eve::exp10(Type(i)), Type(std::pow(10, Type(i))));
    }
  }
}

#endif
