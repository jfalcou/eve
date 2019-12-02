//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sin.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::sin return type")
{
  TTS_EXPR_IS(eve::sin(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::sin behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::sin(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::sin(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::sin(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::sin(Type(1)), Type(std::sin(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::sin(Type(-1)),Type(std::sin(-1.0)), 0.5);
  TTS_IEEE_EQUAL((eve::sin(Type(0))), (Type(1)));
  TTS_IEEE_EQUAL((eve::sin(eve::Mzero<Type>())), (Type(1)));
  TTS_ULP_EQUAL((eve::restricted_(eve::sin)(eve::Pio_4<Type>())), (Type(std::sin(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::sin)(-eve::Pio_4<Type>())),(Type(std::sin(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL(eve::sin(Type(100000.0)), Type(std::sin(100000.0)), 0.5);
  TTS_ULP_EQUAL(eve::sin(Type(-100000.0)),Type(std::sin(-100000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::sin)(Type(-100000000.0))),Type(std::sin(-100000000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::sin)(Type(eve::Valmax<Type>()))),Type(std::sin(eve::Valmax<Value>())), 0.5);

  Value z = eve::Valmax<Value>(); 
 for(int i=1; i < 100; i++)
 {
   std::cout <<  "i =  " << i << std::endl; 
   std::cout << (eve::sin)(Type(z)) << std::endl;
   std::cout << Type(std::sin(z))<< std::endl;
   TTS_ULP_EQUAL((eve::sin)(Type(z)),Type(std::sin(z)), 0.5);
   z = z/10; 
 }
}
