//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cot.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/constant/pio_2.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/all.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::small_(eve::cot) return type")
{
  TTS_EXPR_IS(eve::small_(eve::cot)(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::small_(eve::cot) behavior")
{
  auto my_stdcot =  [](auto x){return eve::rec(std::tan(x));}; 
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::cot)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::cot)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::cot)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::small_(eve::cot)(Type(1)),  Type(my_stdcot(1.0)), 0.5);
  std::cout << eve::small_(eve::cot)(Type(1)) << "   " << Type(my_stdcot(1.0)) << std::endl; 
  TTS_ULP_EQUAL(eve::small_(eve::cot)(Type(-1)), Type(my_stdcot(-1.0)), 0.5); 
  TTS_IEEE_EQUAL((eve::small_(eve::cot)(Type(0))), (eve::Inf<Type>()));
  TTS_IEEE_EQUAL((eve::small_(eve::cot)(eve::Mzero<Type>())), (eve::Minf<Type>()));
  TTS_ULP_EQUAL((eve::small_(eve::cot)(eve::Pio_2<Type>())), (Type(my_stdcot(eve::Pio_2<Value>()))), 3.5);
  TTS_ULP_EQUAL((eve::small_(eve::cot)(-eve::Pio_2<Type>())),(Type(my_stdcot(-eve::Pio_2<Value>()))), 3.5);
  TTS_ULP_EQUAL((eve::small_(eve::cot)(eve::Pio_4<Type>())), (Type(my_stdcot(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::cot)(-eve::Pio_4<Type>())),(Type(my_stdcot(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::cot)(eve::Pio_4<Type>()/2)), (Type(my_stdcot(eve::Pio_4<Value>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::cot)(-eve::Pio_4<Type>()/2)),(Type(my_stdcot(-eve::Pio_4<Value>()/2))), 0.5);
  auto z = eve::Pio_2<Value>(); 
  TTS_ULP_EQUAL((eve::small_(eve::cot)(eve::Pio_2<Type>())), (Type(my_stdcot(eve::Pio_2<Value>()))), 5.5);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::cot)(Type(z))), (Type(my_stdcot(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::cot)(Type(z))), (Type(my_stdcot(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::cot)(Type(z))), (Type(my_stdcot(z))), 0.5);
  
//   while(true)
//   {
//     int i = 1; 
//     z = eve::prev(z);
//     TTS_ULP_EQUAL((eve::small_(eve::cot)(Type(z))), (Type(my_stdcot(z))), 0.5);
//     if (eve::all(eve::ulpdist((eve::small_(eve::cot)(Type(z))), (Type(my_stdcot(z)))) <= 0.5))
//     {
//       std::cout << i << std::endl;
//       std::cout << std::setprecision(20) << z << std::endl;
//       std::cout << eve::small_(eve::cot)(Type(z))<< std::endl;
//    
//       break; 
//     }
//        ++i;
//        if 
//   }
  
}
