//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/function/csc.hpp>
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
#include <cmath>

TTS_CASE("Check eve::csc return type")
{
  TTS_EXPR_IS(eve::csc(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::csc behavior")
{
  auto my_stdcsc =  [](auto x){return eve::rec(std::sin(x));}; 

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::csc)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::csc)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::csc)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::csc)(Type(1)), Type(my_stdcsc(1.0)), 1.0);
  TTS_ULP_EQUAL(eve::medium_(eve::csc)(Type(-1)),Type(my_stdcsc(-1.0)), 1.0);
  TTS_IEEE_EQUAL(eve::medium_(eve::csc)(Type(0)), (Type(my_stdcsc(Value(0.0)))));
  TTS_IEEE_EQUAL(eve::medium_(eve::csc)(eve::Mzero<Type>()), (Type(my_stdcsc(Value(-0.0)))));
  TTS_ULP_EQUAL((eve::medium_(eve::csc)(eve::Pio_4<Type>())), (Type(my_stdcsc(eve::Pio_4<Value>()))), 0.75);
  TTS_ULP_EQUAL((eve::medium_(eve::csc)(-eve::Pio_4<Type>())),(Type(my_stdcsc(-eve::Pio_4<Value>()))), 0.75);
  TTS_ULP_EQUAL((eve::medium_(eve::csc)(Type(100.0))), Type(my_stdcsc(Value(100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium_(eve::csc)(Type(-100.0))),Type(my_stdcsc(Value(-100.0))), 1.5);
  TTS_ULP_EQUAL((eve::medium_(eve::csc)(Type(100000.0))), Type(my_stdcsc(Value(100000.0))), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::csc)(Type(-100000.0))),Type(my_stdcsc(Value(-100000.0))), 0.5);
  auto z =  eve::Ieee_constant < Value, 0x58d776beU,  0x42F0000000000000ULL >(); // 1.76859e+15 (float) et  281474976710656.0 (double)
  int i = 0; 
  while(true)
  {
    ++i; 
    TTS_ULP_EQUAL(eve::medium_(eve::csc)(Type(z)),Type(my_stdcsc(Value(z))), 1.5);
    z/= 5.123;
    if (i == 0) break; 
    if (eve::all(eve::is_eqz(z))) break;
  }
}

