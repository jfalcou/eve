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

TTS_CASE("Check eve::medium_(eve::csc) return type")
{
  TTS_EXPR_IS(eve::csc(Type(0)), (Type));
}

TTS_CASE("Check eve::medium_(eve::csc) behavior")
{
  auto my_stdcsc =  [](auto x){return eve::rec(std::sin(double(x)));}; 

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
}

