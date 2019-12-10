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
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
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
    TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::big_(eve::cos)(Type(1)), Type(std::cos(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::cos)(Type(-1)),Type(std::cos(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::cos)(Type(0)), (Type(1)));
  TTS_IEEE_EQUAL(eve::big_(eve::cos)(eve::Mzero<Type>()), (Type(1)));
  TTS_ULP_EQUAL((eve::big_(eve::cos)(eve::Pio_4<Type>())), (Type(std::cos(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(-eve::Pio_4<Type>())),(Type(std::cos(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(Type(100000.0))), Type(std::cos(100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(Type(-100000.0))),Type(std::cos(-100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(Type(100000000.0))), Type(std::cos(100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(Type(-100000000.0))),Type(std::cos(-100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(Type(eve::Valmax<Type>()))),Type(std::cos(eve::Valmax<Value>())), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::cos)(Type(eve::Valmax<Type>()))/10),Type(std::cos(eve::Valmax<Value>())/10), 0.5);

  Value z =  eve::Valmax<Value>(); 
  while(true)
  {
    TTS_ULP_EQUAL(eve::big_(eve::cos)(Type(z)),Type(std::cos(Value(z))), 0.5);
    z/= 5.123;
    if (eve::all(eve::is_eqz(z))) break; 
 }
}
