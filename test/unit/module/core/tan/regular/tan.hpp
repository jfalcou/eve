//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tan.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/any.hpp>
#include <eve/function/ulpdist.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::tan return type")
{
  TTS_EXPR_IS(eve::tan(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::tan behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::tan(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::tan(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::tan(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::tan(Type(1)), Type(std::tan(Value(1.0))), 0.5);
  TTS_ULP_EQUAL(eve::tan(Type(-1.0)),Type(std::tan(Value(-1.0))), 0.5);
  TTS_IEEE_EQUAL((eve::tan(Type(0))), (Type(0)));
  TTS_IEEE_EQUAL((eve::tan(eve::Mzero<Type>())), (Type(0)));
  TTS_ULP_EQUAL((eve::tan(eve::Pio_4<Type>())), (Type(std::tan(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::tan(-eve::Pio_4<Type>())),(Type(std::tan(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL(eve::tan(Type(100000.0)), Type(std::tan(100000.0)), 0.5);
  TTS_ULP_EQUAL(eve::tan(Type(-100000.0)),Type(std::tan(-100000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::tan)(Type(-100000000.0))),Type(std::tan(-100000000.0)), 0.5);
  TTS_ULP_EQUAL(((eve::tan)(Type(eve::Valmax<Type>()))),Type(std::tan(eve::Valmax<Value>())), 0.5);
  
  Value z =  eve::Valmax<Value>(); 
  while(true)
  {
    TTS_ULP_EQUAL(eve::big_(eve::tan)(Type(z)),Type(std::tan(Value(z))), 1.0);
    z/= 5.1234;
    if (eve::all(eve::is_eqz(z))) break; 
  }
}
