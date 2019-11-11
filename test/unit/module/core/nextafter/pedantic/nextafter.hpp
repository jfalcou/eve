//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/nextafter.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/nan.hpp>
#include <type_traits>

TTS_CASE("Check nextafter return type")
{
  TTS_EXPR_IS((eve::pedantic_(eve::nextafter)(Type(), Type())), (Type));
  TTS_EXPR_IS((eve::pedantic_(eve::nextafter)(Type(), Value())), (Type));
  TTS_EXPR_IS((eve::pedantic_(eve::nextafter)(Value(), Type())), (Type));
}

TTS_CASE("Check eve::pedantic_(eve::nextafter) one parameter behavior")
{
  if constexpr(std::is_integral_v<Value>)
  {
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type{1}, Type{1})), Type(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type{1}, Type{5})), Type(2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type{2}, Type(0))), Type(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Value{1}, Type{1})), Type(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Value{1}, Type{5})), Type(2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Value{2}, Type(0))), Type(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type{1}, Value{1})), Type(1));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type{1}, Value{5})), Type(2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type{2}, Value(0))), Type(1));

    if constexpr(std::is_signed_v<Value>)
    {
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type(-1), Type(-1))), Type(-1));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type(-1), Type(5))), Type(0));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Value(-2), Type(-4))), Type(-3));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Value(-1), Type(-1))), Type(-1));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Value(-1), Type(5))), Type(0));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Value(-2), Type(-4))), Type(-3));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type(-1), Value(-1))), Type(-1));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type(-1), Value(5))), Type(0));
      TTS_EQUAL((eve::pedantic_(eve::nextafter)(Type(-2), Value(-4))), Type(-3));
    }
    
  }
  else
  {
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::Mone<Type>(), Type(2)))        , (eve::Mone<Type>()+eve::Eps<Type>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<Type>(), Type(-1)))        , (eve::One<Type>()-eve::Eps<Type>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<Type>(), Type(1)))        , (eve::One<Type>()));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::Mone<Value>(), Type(2)))       , (eve::Mone<Type>()+eve::Eps<Type>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<Value>(), Type(-1)))       , (eve::One<Type>()-eve::Eps<Type>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<Value>(), Type(1)))       , (eve::One<Type>()));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::Mone<Type>(), Value(2)))       , (eve::Mone<Type>()+eve::Eps<Type>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<Type>(), Value(-1)))       , (eve::One<Type>()-eve::Eps<Type>()/2));
    TTS_EQUAL((eve::pedantic_(eve::nextafter)(eve::One<Value>(), Type(1)))       , (eve::One<Type>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(eve::Nan<Type>(), Type(1)))         , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(Type(1), eve::Nan<Type>()))         , (eve::Nan<Type>()));    
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(eve::Nan<Value>(), Type(1)))         , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(Value(1), eve::Nan<Type>()))         , (eve::Nan<Type>()));    
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(eve::Nan<Type>(), Value(1)))         , (eve::Nan<Type>()));
    TTS_IEEE_EQUAL((eve::pedantic_(eve::nextafter)(Type(1), eve::Nan<Value>()))         , (eve::Nan<Type>()));    
  }
}
