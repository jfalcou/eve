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
#include <eve/constant/pio_2.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <utility>
#include <cmath>

TTS_CASE("Check sincos return type")
{
  TTS_EXPR_IS(eve::small_(eve::sincos)(Type()), (std::tuple<Type,Type>));
} 

TTS_CASE("Check (eve::sincos behavior")
{
  static const int N = 9; 
  Value x[N] = {  eve::Pi<Value>()/8, -eve::Pi<Value>()/8
                  , eve::Pi<Value>()/4, -eve::Pi<Value>()/4
                  , 3*eve::Pi<Value>()/8, -3*eve::Pi<Value>()/8  
                  , eve::Pio_2<Value>(), -eve::Pi<Value>()/2, Value(1.57079632679489655800e+00)
  }; 
  
  for(int i=0; i < N ; ++i) 
  {
    auto [p0, p1] = eve::small_(eve::sincos)(Type(x[i]));
    TTS_ULP_EQUAL(p0, Type(std::sin(x[i])), 3.5);
    TTS_ULP_EQUAL(p1, Type(std::cos(x[i])), 3.5);
  } 
}
