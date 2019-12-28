//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sec.hpp>
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

TTS_CASE("Check eve::small_(eve::sec) return type")
{
  TTS_EXPR_IS(eve::small_(eve::sec)(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::small_(eve::sec) behavior")
{
  auto my_stdsec =  [](auto x){return eve::rec(std::cos(x));}; 
  
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::small_(eve::sec)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sec)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::small_(eve::sec)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::small_(eve::sec)(Type(1)),  Type(my_stdsec(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::small_(eve::sec)(Type(-1)), Type(my_stdsec(-1.0)), 0.5); 
  TTS_IEEE_EQUAL((eve::small_(eve::sec)(Type(0))), (eve::One<Type>()));
  TTS_IEEE_EQUAL((eve::small_(eve::sec)(eve::Mzero<Type>())), (eve::One<Type>()));
  TTS_ULP_EQUAL((eve::small_(eve::sec)(eve::Pio_2<Type>())), (Type(my_stdsec(eve::Pio_2<Value>()))), 5.5);
  TTS_ULP_EQUAL((eve::small_(eve::sec)(-eve::Pio_2<Type>())),(Type(my_stdsec(-eve::Pio_2<Value>()))), 5.5);
  TTS_ULP_EQUAL((eve::small_(eve::sec)(eve::Pio_4<Type>())), (Type(my_stdsec(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sec)(-eve::Pio_4<Type>())),(Type(my_stdsec(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sec)(eve::Pio_4<Type>()/2)), (Type(my_stdsec(eve::Pio_4<Value>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::small_(eve::sec)(-eve::Pio_4<Type>()/2)),(Type(my_stdsec(-eve::Pio_4<Value>()/2))), 0.5);
  auto z = eve::Pio_2<Value>(); 
  TTS_ULP_EQUAL((eve::small_(eve::sec)(eve::Pio_2<Type>())), (Type(my_stdsec(eve::Pio_2<Value>()))), 5.5);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::sec)(Type(z))), (Type(my_stdsec(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::sec)(Type(z))), (Type(my_stdsec(z))), 1);
  z = eve::prev(z); 
  TTS_ULP_EQUAL((eve::small_(eve::sec)(Type(z))), (Type(my_stdsec(z))), 0.5);

  
}
