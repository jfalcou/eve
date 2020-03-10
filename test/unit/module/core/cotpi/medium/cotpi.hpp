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
#include <eve/function/sin.hpp>    
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/next.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/half.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::cotpi return type")
{
  TTS_EXPR_IS(eve::cotpi(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::cotpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::cotpi)(Type(1)), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::cotpi)(Type(-1)),eve::Nan<Type>(), 0.5);
  TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(Type(0)), (eve::Inf<Type>()));
  TTS_IEEE_EQUAL(eve::medium_(eve::cotpi)(eve::Mzero<Type>()), (eve::Minf<Type>()));
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(Type(22.5))), (Type(0)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(-Type(22.5))),(Type(0)), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(Type(100000.0))), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(Type(-100000.0))),eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(Type(100000000.0))), eve::Nan<Type>(), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::cotpi)(Type(-100000000.0))),eve::Nan<Type>(), 0.5);
}

