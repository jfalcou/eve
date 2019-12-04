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
#include <eve/constant/ieee_constant.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::cot return type")
{
  TTS_EXPR_IS(eve::cot(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cot behavior")
{
  auto my_stdcot =  [](auto x){return eve::rec(std::tan(x));}; 

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::cot)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cot)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cot)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::cot)(Type(1)), Type(my_stdcot(1.0)), 1.0);
  TTS_ULP_EQUAL(eve::medium_(eve::cot)(Type(-1)),Type(my_stdcot(-1.0)), 1.0);
  TTS_IEEE_EQUAL(eve::medium_(eve::cot)(Type(0)), (eve::Inf<Type>()));
  TTS_IEEE_EQUAL(eve::medium_(eve::cot)(eve::Mzero<Type>()), (eve::Minf<Type>()));
  TTS_ULP_EQUAL((eve::medium_(eve::cot)(eve::Pio_4<Type>())), (Type(my_stdcot(eve::Pio_4<Value>()))), 0.75);
  TTS_ULP_EQUAL((eve::medium_(eve::cot)(-eve::Pio_4<Type>())),(Type(my_stdcot(-eve::Pio_4<Value>()))), 0.75);
  TTS_ULP_EQUAL((eve::medium_(eve::cot)(Type(100.0))), Type(my_stdcot(Value(100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cot)(Type(-100.0))),Type(my_stdcot(Value(-100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cot)(Type(100000.0))), Type(my_stdcot(Value(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cot)(Type(-100000.0))),Type(my_stdcot(Value(-100000.0))), 0.5);
  auto z =  eve::Ieee_constant < Value, 0x58d776beU,  0x42F0000000000000ULL >(); // 1.76859e+15 (float) et  281474976710656.0 (double)
  while(true)
  {
    std::cout << std::setprecision(20) << "z " << z << std::endl; 
    TTS_ULP_EQUAL(eve::medium_(eve::cot)(Type(z)),Type(my_stdcot(Value(z))), 1.5);
    z/= 5.123;
    if (eve::all(eve::is_eqz(z))) break;
  }
}

