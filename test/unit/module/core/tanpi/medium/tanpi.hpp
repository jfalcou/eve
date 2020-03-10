//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/tanpi.hpp>
#include <eve/function/sin.hpp>    
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/function/next.hpp>
#include <eve/constant/pi.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>  
#include <eve/function/all.hpp>
#include <eve/function/is_positive.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::tanpi return type")
{
  TTS_EXPR_IS(eve::tanpi(Type(0)), (Type));
}

TTS_CASE("Check eve::eve::tanpi behavior")
{
  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::medium_(eve::tanpi)(eve::Nan<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::tanpi)(eve::Inf<Type>()) , (eve::Nan<Type>()) );
    TTS_IEEE_EQUAL(eve::medium_(eve::tanpi)(eve::Minf<Type>()), (eve::Nan<Type>()) );   
  }
  TTS_ULP_EQUAL(eve::medium_(eve::tanpi)(Type(1)), Type(0), 0.5);
  TTS_ULP_EQUAL(eve::medium_(eve::tanpi)(Type(-1)),Type(0), 0.5);
  TTS_IEEE_EQUAL(eve::medium_(eve::tanpi)(Type(0)), (Type(0)));
  TTS_EXPECT(eve::all(eve::is_positive(eve::medium_(eve::tanpi)(eve::Zero<Type>()))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::medium_(eve::tanpi)(eve::Mzero<Type>()))));    
  TTS_IEEE_EQUAL(eve::medium_(eve::tanpi)(eve::Mzero<Type>()), (Type(0)));
  TTS_ULP_EQUAL((eve::medium_(eve::tanpi)(Type(22.5))), (eve::Nan<Type>()), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tanpi)(-Type(22.5))),(eve::Nan<Type>()), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tanpi)(Type(100000.0))), Type(0), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tanpi)(Type(-100000.0))),Type(0), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tanpi)(Type(100000000.0))), Type(0), 0.5);
  TTS_ULP_EQUAL((eve::medium_(eve::tanpi)(Type(-100000000.0))),Type(0), 0.5);
}

