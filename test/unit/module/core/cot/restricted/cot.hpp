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
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted_(eve::cot) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::cot)(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::restricted_(eve::cot) behavior")
{
  auto my_stdcot =  [](auto x){return eve::rec(std::tan(x));}; 

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::cot)(Type(1)), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::cot)(Type(-1)),eve::Nan<Type>(), 0.5);
  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(Type(0)), (eve::Inf<Type>()));
  TTS_IEEE_EQUAL(eve::restricted_(eve::cot)(eve::Mzero<Type>()), (eve::Minf<Type>()));
  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(eve::Pio_4<Type>())), (Type(my_stdcot(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(-eve::Pio_4<Type>())),(Type(my_stdcot(-eve::Pio_4<Value>()))), 0.5);
  
  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(eve::Pio_4<Type>()/2)), (Type(my_stdcot(eve::Pio_4<Value>()/2))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cot)(-eve::Pio_4<Type>()/2)),(Type(my_stdcot(-eve::Pio_4<Value>()/2))), 0.5);
  auto z =  eve::Pio_4<Value>();
  int i = 0; 
  while(true)
  {
    ++i; 
    TTS_ULP_EQUAL(eve::restricted_(eve::cot)(Type(z)),Type(my_stdcot(Value(z))), 0.5);
    z/= 5.123;
    if (i == 300) break; 
    if (eve::all(eve::is_eqz(z))) break;
  } 
}
