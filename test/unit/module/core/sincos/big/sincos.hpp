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
#include <eve/function/sin.hpp>
#include <eve/function/cos.hpp>    
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>
#include <cmath>

TTS_CASE("Check sincos return type")
{
  TTS_EXPR_IS(eve::big(eve::sincos(Type())), (std::tuple<Type,Type>));
} 

TTS_CASE("Check (eve::sincos behavior")
{
  static const int N = 16; 
  Value x[N] = {  eve::Pi<Value>()/8, -eve::Pi<Value>()/8
                  , eve::Pi<Value>()/4, -eve::Pi<Value>()/4
                  , Value(1), Value(-1)
                  , Value(10), Value(-10)
                  , Value(1000000), Value(-1000000)
                  , Value(1000000000), Value(-1000000000)
                  , eve::Valmax<Value>(), eve::Valmin<Value>()    
                  , eve::Valmax<Value>()/100000, eve::Valmin<Value>()/10000}; 
  
  for(int i=0; i < N ; ++i)
  {
    Type p0, p1; 
    std::tie(p0, p1) = eve::big_(eve::sincos)(Type(x[i]));
    TTS_ULP_EQUAL(p0, Type(std::sin(x[i])), 0.5);
    TTS_ULP_EQUAL(p1, Type(std::cos(x[i])), 0.5);
  }
}
