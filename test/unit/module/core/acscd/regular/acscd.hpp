//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/acscd.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::acscd return type")
{
  TTS_EXPR_IS(eve::acscd(Type(0)), (Type));
}

TTS_CASE("Check eve::acscd behavior")
{
  if constexpr( eve::platform::supports_nans )
  {
    TTS_ULP_EQUAL(eve::acscd(Type(0))           , eve::Nan<Type>(), 1);
    TTS_ULP_EQUAL(eve::acscd(eve::Mzero<Type>()), eve::Nan<Type>(), 1);
    TTS_IEEE_EQUAL(eve::acscd(eve::Nan<Type>()) , (eve::Nan<Type>()) );
  }

  if constexpr( eve::platform::supports_infinites )
  {
    TTS_IEEE_EQUAL(eve::acscd(eve::Inf<Type>())  , (Type(0)) );
    TTS_IEEE_EQUAL(eve::acscd(eve::Minf<Type>()) , (Type(0)) );
  }

  TTS_ULP_EQUAL(eve::acscd(Type(-2.)),  -Type(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(Type( 2.)),   Type(30), 1  );
  TTS_ULP_EQUAL(eve::acscd(Type(-1.)),  -Type(90), 0.5);
  TTS_ULP_EQUAL(eve::acscd(Type( 1.)),   Type(90), 0.5);
}
