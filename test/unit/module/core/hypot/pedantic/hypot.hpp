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
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(Type(0), Type(0)), (Type));
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(Value(0), Type(0)), (Type));
  TTS_EXPR_IS(eve::pedantic_(eve::hypot)(Type(0), Value(0)), (Type));
}

TTS_CASE("Check eve::pedantic_(eve::hypot) behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Nan<Type>()), eve::Inf<Type>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<Value>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Value>(), eve::Nan<Type>()), eve::Inf<Type>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Nan<Type>(), eve::Inf<Value>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Nan<Value>()), eve::Inf<Type>(), 0);
  }

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Type>(), (Type(0)))          , eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type(0))          , eve::Valmax<Type>()), eve::Valmax<Type>(), 0);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Value>(), (Type(0)))          , eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Value(0))          , eve::Valmax<Type>()), eve::Valmax<Type>(), 0);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Type>(), (Value(0)))          , eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type(0))          , eve::Valmax<Value>()), eve::Valmax<Type>(), 0);


  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Type>()/2, eve::Valmax<Type>()/2), eve::Valmax<Type>()/eve::Sqrt_2<Type>(), 0.5); 
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Value>()/2, eve::Valmax<Type>()/2), eve::Valmax<Type>()/eve::Sqrt_2<Type>(), 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Type>()/2, eve::Valmax<Value>()/2), eve::Valmax<Type>()/eve::Sqrt_2<Type>(), 0.5);
  
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Value(-1)), (Type(-1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Value( 1)), (Type( 1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Value( 0)), (Type( 0)))                  , (Type(0))           , 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<Value>(), eve::Sqrt_2<Type>()), Type(2)             , 0.5);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type(-1)), (Value(-1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type( 1)), (Value( 1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type( 0)), (Value( 0)))                  , (Type(0))           , 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<Type>(), eve::Sqrt_2<Value>()), Type(2)             , 0.5);

  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type(-1)), (Type(-1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type( 1)), (Type( 1)))                  , eve::Sqrt_2<Type>() , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type( 0)), (Type( 0)))                  , (Type(0))           , 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Sqrt_2<Type>(), eve::Sqrt_2<Type>()), Type(2)             , 0.5);
}


TTS_CASE("Check pedantic_ 3 params eve::hypot behavior")
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Value>(), eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Value>(), eve::Inf<Type>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Inf<Value>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Inf<Value>(), eve::Inf<Type>()), eve::Inf<Type>(), 0);

    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Inf<Value>(), eve::Inf<Value>()), eve::Inf<Type>(), 0);
    TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Inf<Type>(), eve::Inf<Value>(), eve::Inf<Value>()), eve::Inf<Type>(), 0);

  }
  
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)(eve::Valmax<Type>(), (Type(0)),            (Type(0)))          , eve::Valmax<Type>(), 0);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type(0))          , (eve::Valmax<Type>()),  (Type(0))),        eve::Valmax<Type>(), 0);
  
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type(-1)), (Type(-1)), (eve::Sqrt_2<Type>()))                   , Type(2) , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type( 1)), (Type( 1)), (eve::Sqrt_2<Type>()))                   , Type(2) , 0.5);
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type( 0)), (Type( 0)), (Type( 0)))                             , (Type(0)), 0  );
  TTS_ULP_EQUAL(eve::pedantic_(eve::hypot)((Type( 1)), (Type( 1)), (Type( 1)))                             , Type(std::sqrt(Value(3))), 0.5); 
}
