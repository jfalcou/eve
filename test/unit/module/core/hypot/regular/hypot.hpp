//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/hypot.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/platform.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check hypot return type")
{
  TTS_EXPR_IS(eve::hypot(Type(0), Type(0)), (Type));
}

TTS_CASE("Check eve::hypot behavior")
{
  // non conforming to standard
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::hypot(eve::Nan<Type>(), eve::Inf<Type>()), eve::Nan<Type>(), 0);
    TTS_ULP_EQUAL(eve::hypot(eve::Inf<Type>(), eve::Nan<Type>()), eve::Nan<Type>(), 0);
  }

  TTS_ULP_EQUAL(eve::hypot(eve::Valmax<Type>(), (Type(0)))          , eve::Inf<Type>(), 0);
  TTS_ULP_EQUAL(eve::hypot((Type(0))          , eve::Valmax<Type>()), eve::Inf<Type>(), 0);

  TTS_ULP_EQUAL(eve::hypot((Type(-1)), (Type(-1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::hypot((Type( 1)), (Type( 1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::hypot((Type( 0)), (Type( 0)))                  , (Type(0))           , 0  );
  TTS_ULP_EQUAL(eve::hypot(eve::Sqrt_2<Type>(), eve::Sqrt_2<Type>()), Type(2)             , 0.5);
}
