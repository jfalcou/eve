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
#include <eve/function/all.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::big_(eve::tan) return type")
{
  TTS_EXPR_IS(eve::big_(eve::tan)(Type(0)), (Type));
}

TTS_CASE("Check eve::big_(eve::tan) behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::big_(eve::tan)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::tan)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::big_(eve::tan)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::big_(eve::tan)(Type(1)), Type(std::tan(1.0)), 0.5);
  TTS_ULP_EQUAL(eve::big_(eve::tan)(Type(-1)),Type(std::tan(-1.0)), 0.5);
  TTS_IEEE_EQUAL(eve::big_(eve::tan)(Type(0)), (Type(0)));
  TTS_IEEE_EQUAL(eve::big_(eve::tan)(eve::Mzero<Type>()), (Type(0)));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::tan)(eve::Mzero<Type>()))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::tan)(eve::Zero<Type>()))));
  TTS_ULP_EQUAL((eve::big_(eve::tan)(eve::Pio_4<Type>())), (Type(std::tan(eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::tan)(-eve::Pio_4<Type>())),(Type(std::tan(-eve::Pio_4<Value>()))), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::tan)(Type(100000.0))), Type(std::tan(100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::tan)(Type(-100000.0))),Type(std::tan(-100000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::tan)(Type(100000000.0))), Type(std::tan(100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::tan)(Type(-100000000.0))),Type(std::tan(-100000000.0)), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::tan)(Type(eve::Valmax<Type>()))),Type(std::tan(eve::Valmax<Value>())), 0.5);
  TTS_ULP_EQUAL((eve::big_(eve::tan)(Type(eve::Valmax<Type>()))/10),Type(std::tan(eve::Valmax<Value>())/10), 0.5);     
}
