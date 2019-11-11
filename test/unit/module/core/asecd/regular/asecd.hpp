//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/asecd.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

TTS_CASE("Check eve::asecd return type")
{
  TTS_EXPR_IS(eve::asecd(Type(0)), (Type));
}

TTS_CASE("Check eve::asecd behavior")
{
  if constexpr( eve::platform::supports_infinites )
  {
    TTS_ULP_EQUAL(eve::asecd(eve::Inf<Type>()) , (Type(90)), 0.5);
    TTS_ULP_EQUAL(eve::asecd(eve::Minf<Type>()), (Type(90)), 0.5);
  }

  if constexpr( eve::platform::supports_nans )
  {
    TTS_IEEE_EQUAL(eve::asecd(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_ULP_EQUAL(eve::asecd(Type(0))           , eve::Nan<Type>(), 1);
    TTS_ULP_EQUAL(eve::asecd(eve::Mzero<Type>()), eve::Nan<Type>(), 1);
  }

  TTS_ULP_EQUAL(eve::asecd(Type(-2.)), (Type(360)/3) , 1   );
  TTS_ULP_EQUAL(eve::asecd(Type( 2.)), (Type(180)/3) , 1   );
  TTS_ULP_EQUAL(eve::asecd(Type(-1.)), (Type(180))   , 0.5 );
  TTS_ULP_EQUAL(eve::asecd(Type( 1.)), (Type(0))     , 0.5 );
}
