//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/div.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE("Check div return type")
{
  TTS_EXPR_IS(eve::div(Type(), Type() , eve::to_nearest_), (Type));
  TTS_EXPR_IS(eve::div(Type(), Value() , eve::to_nearest_), (Type));
  TTS_EXPR_IS(eve::div(Value(), Type() , eve::to_nearest_), (Type));
}

TTS_CASE("Check eve::div behavior")
{
  if constexpr(std::is_integral_v<Type> && std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::div(eve::Mone<Type>()  , Type{2} , eve::to_nearest_), Type(0));
    TTS_EQUAL(eve::div(eve::Mone<Value>() , Type{2} , eve::to_nearest_), Type(0));
    TTS_EQUAL(eve::div(eve::Mone<Type>()  , Value{2}, eve::to_nearest_), Type(0));
  }
  TTS_EQUAL(eve::div(Type{12}, Type{4}, eve::to_nearest_), Type{3});
  TTS_EQUAL(eve::div(Type{1} , Type{2}, eve::to_nearest_), Type(0));
  TTS_EQUAL(eve::div(Type{3} , Type{2}, eve::to_nearest_), Type(2));
  TTS_EQUAL(eve::div(Type{4} , Type{3}, eve::to_nearest_), Type(1));

  TTS_EQUAL(eve::div(Value{12}, Type{4}, eve::to_nearest_), Type{3});
  TTS_EQUAL(eve::div(Value{1} , Type{2}, eve::to_nearest_), Type(0));
  TTS_EQUAL(eve::div(Value{3} , Type{2}, eve::to_nearest_), Type(2));
  TTS_EQUAL(eve::div(Value{4} , Type{3}, eve::to_nearest_), Type(1));

  TTS_EQUAL(eve::div(Type{12}, Value{4}, eve::to_nearest_), Type{3});
  TTS_EQUAL(eve::div(Type{1} , Value{2}, eve::to_nearest_), Type(0));
  TTS_EQUAL(eve::div(Type{3} , Value{2}, eve::to_nearest_), Type(2));
  TTS_EQUAL(eve::div(Type{4} , Value{3}, eve::to_nearest_), Type(1));
}
