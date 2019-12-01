//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cos.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cos return type")
{
  TTS_EXPR_IS(eve::cos(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cos behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::cos(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    std::cout << eve::cos(eve::Nan<Type>()) << std::endl; 
    TTS_IEEE_EQUAL(eve::cos(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    std::cout << eve::cos(eve::Inf<Type>()) << std::endl; 
    TTS_IEEE_EQUAL(eve::cos(eve::Minf<Type>()), (eve::Nan<Type>()) );   
    std::cout << eve::cos(eve::Minf<Type>()) << std::endl; 
  }
//   TTS_ULP_EQUAL(eve::cos(Type(1)), Type(std::cos(1.0)), 0.5);
//   TTS_ULP_EQUAL(eve::cos(Type(-1)),Type(std::cos(-1.0)), 0.5);
//   TTS_IEEE_EQUAL((eve::cos(Type(0))), (Type(1)));
//   TTS_IEEE_EQUAL((eve::cos(eve::Mzero<Type>())), (Type(1)));
//   TTS_ULP_EQUAL((eve::restricted_(eve::cos)(eve::Pio_4<Type>())), (Type(std::cos(eve::Pio_4<Value>()))), 0.5);
//   TTS_ULP_EQUAL((eve::restricted_(eve::cos)(-eve::Pio_4<Type>())),(Type(std::cos(-eve::Pio_4<Value>()))), 0.5);
//   TTS_ULP_EQUAL(eve::cos(Type(100000.0)), Type(std::cos(100000.0)), 0.5);
//   TTS_ULP_EQUAL(eve::cos(Type(-100000.0)),Type(std::cos(-100000.0)), 0.5);
//   TTS_ULP_EQUAL(((eve::cos)(Type(-100000000.0))),Type(std::cos(-100000000.0)), 0.5);
//   TTS_ULP_EQUAL(((eve::cos)(Type(eve::Valmax<Type>()))),Type(std::cos(eve::Valmax<Value>())), 0.5);

//   Value z = eve::Valmax<Value>(); 
//  for(int i=1; i < 100; i++)
//  {
//    std::cout <<  "i =  " << i << std::endl; 
// //    std::cout << (eve::cos)(Type(z)) << std::endl;
// //    std::cout << Type(std::cos(z))<< std::endl;
//    TTS_ULP_EQUAL((eve::cos)(Type(z)),Type(std::cos(z)), 0.5);
//    z = z/10; 
//  }
}
