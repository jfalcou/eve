//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sinpi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pio_4.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted_(eve::sinpi) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::sinpi)(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::restricted_(eve::sinpi) behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::sinpi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::restricted_(eve::sinpi)(Type(1)), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::restricted_(eve::sinpi)(Type(-1)),eve::Nan<Type>(), 0.5);
  TTS_IEEE_EQUAL((eve::restricted_(eve::sinpi)(Type(0))), (Type(0)));
  TTS_IEEE_EQUAL((eve::restricted_(eve::sinpi)(eve::Mzero<Type>())), (Type(0)));
  TTS_ULP_EQUAL((eve::restricted_(eve::sinpi)(Type(0.25))), (Type(std::sin(eve::Pio_4<double>()))), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::sinpi)(-Type(0.25))),(Type(std::sin(-eve::Pio_4<double>()))), 0.5);
  
}
