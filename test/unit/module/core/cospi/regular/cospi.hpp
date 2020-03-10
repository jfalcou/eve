//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cospi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cospi return type")
{
  TTS_EXPR_IS(eve::cospi(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cospi behavior")
{

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL((eve::cospi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL((eve::cospi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL((eve::cospi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL((eve::cospi)(Type(1)), Type(-1), 0.5);
  TTS_ULP_EQUAL((eve::cospi)(Type(-1)),Type(-1), 0.5);
  TTS_IEEE_EQUAL((eve::cospi)(Type(0)), (Type(1)));
  TTS_IEEE_EQUAL((eve::cospi)(eve::Mzero<Type>()), (Type(1)));
  TTS_ULP_EQUAL(((eve::cospi)(Type(22.5))), (Type(0)), 0.5);
  TTS_ULP_EQUAL(((eve::cospi)(-Type(22.5))),(Type(0)), 0.5);
  TTS_ULP_EQUAL(((eve::cospi)(Type(100000.0))), Type(1), 0.5);
  TTS_ULP_EQUAL(((eve::cospi)(Type(-100000.0))),Type(1), 0.5);
  TTS_ULP_EQUAL(((eve::cospi)(Type(100000000.0))), Type(1), 0.5);
  TTS_ULP_EQUAL(((eve::cospi)(Type(-100000000.0))),Type(1), 0.5);
  TTS_ULP_EQUAL(((eve::cospi)(Type(eve::Valmax<Type>()))),Type(1), 0.5);
  TTS_ULP_EQUAL(((eve::cospi)(Type(eve::Valmax<Type>()/10))),Type(1), 0.5);
}
