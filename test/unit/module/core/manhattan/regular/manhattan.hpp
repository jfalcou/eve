//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/manhattan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <cmath>

TTS_CASE("Check manhattan return type")
{ 
  TTS_EXPR_IS(eve::manhattan(Type(0), Type(0)), (Type));
}

TTS_CASE("Check eve::manhattan behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::manhattan(eve::Nan<Type>(), eve::Inf<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::manhattan(eve::Inf<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
  }

  TTS_ULP_EQUAL(eve::manhattan(eve::Valmax<Type>(), (Type(0)))          , eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::manhattan((Type(0))          , eve::Valmax<Type>()), eve::Valmax<Type>(), 0);

  TTS_ULP_EQUAL(eve::manhattan((Type(-1)), (Type(-1)))                  , Type(2)                     , 0);
  TTS_ULP_EQUAL(eve::manhattan((Type( 1)), (Type( 1)))                  , Type(2)                     , 0);
  TTS_ULP_EQUAL(eve::manhattan((Type( 0)), (Type( 0)))                  , (Type(0))                   , 0  );
  TTS_ULP_EQUAL(eve::manhattan(eve::Sqrt_2<Type>(), eve::Sqrt_2<Type>()), Type(2)* eve::Sqrt_2<Type>(), 0.5);
}

TTS_CASE("Check 3 params eve::manhattan behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::manhattan(eve::Nan<Type>(), eve::Inf<Type>(), eve::Inf<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::manhattan(eve::Inf<Type>(), eve::Nan<Type>(), eve::Inf<Type>()), eve::Nan<Type>(), 0); 
  }
  
  TTS_ULP_EQUAL(eve::manhattan(eve::Valmax<Type>(), (Type(0)),              (Type(0))), eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::manhattan((Type(0))          , (eve::Valmax<Type>()),  (Type(0))), eve::Valmax<Type>(), 0);
  
  TTS_ULP_EQUAL(eve::manhattan((Type(-1)), (Type(-1)), Type(-1)), Type(3) , 0);
  TTS_ULP_EQUAL(eve::manhattan((Type( 1)), (Type( 1)), Type(-1)), Type(3) , 0);
  TTS_ULP_EQUAL(eve::manhattan((Type( 0)), (Type( 0)), (Type( 0))), Type(0), 0);
  TTS_ULP_EQUAL(eve::manhattan((Type( 1)), (Type( 1)), (Type( 1))), Type(3), 0); 
}
