//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sincos.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>
#include <cmath>

TTS_CASE("Check sincos  return type")
{
  TTS_EXPR_IS((eve::restricted_(eve::sincos)(Type())), (std::tuple<Type,Type>));
}

TTS_CASE("Check (eve::sincos behavior")
{
  static const int N = 6; 
  Value x[N] = {   eve::Pi<Value>()/8, -eve::Pi<Value>()/8
                   , eve::Pi<Value>()/4, -eve::Pi<Value>()/4
                   , Value(1), Value(-1)}; 
  
  for(int i=0; i < 4 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sincos)(Type(x[i]));
    TTS_ULP_EQUAL(p0, Type(std::sin(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, Type(std::cos(x[i])), 0.5);
  }
  for(int i=4; i < 6 ; ++i)
  {
    auto [p0, p1] = eve::restricted_(eve::sincos)(Type(x[i]));
    TTS_ULP_EQUAL(p0, eve::Nan<Type>(), 0.5);
    TTS_ULP_EQUAL(p1, eve::Nan<Type>(), 0.5);
  }
}
