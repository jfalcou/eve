//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/cotpi.hpp>
#include <eve/function/cos.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/rec.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check eve::restricted_(eve::cotpi) return type")
{
  TTS_EXPR_IS(eve::restricted_(eve::cotpi)(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cotpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(Type(0)), (eve::Inf<Type>()));
  TTS_IEEE_EQUAL(eve::restricted_(eve::cotpi)(eve::Mzero<Type>()), (eve::Minf<Type>()));
  TTS_ULP_EQUAL((eve::restricted_(eve::cotpi)(Type(0.125))), (Type(2.414213562373095048801688724209698078569671875377)), 0.5);
  TTS_ULP_EQUAL((eve::restricted_(eve::cotpi)(Type(-0.125))), (Type(-2.414213562373095048801688724209698078569671875377)), 0.5);
}
