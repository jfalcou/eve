//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/rem.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <type_traits>

TTS_CASE("Check rem return type")
{
  TTS_EXPR_IS(eve::rem(Type(), Type() ), (Type));
  TTS_EXPR_IS(eve::rem(Type(), Value() ), (Type));
  TTS_EXPR_IS(eve::rem(Value(), Type() ), (Type));
}

TTS_CASE("Check eve::rem behavior")
{
  if constexpr(std::is_integral_v<Type> && std::is_signed_v<Type>)
  {
    TTS_EQUAL(eve::rem(eve::Mone<Type>()  , Type{2} ), Type(-1));
    TTS_EQUAL(eve::rem(eve::Mone<Value>() , Type{2} ), Type(-1));
    TTS_EQUAL(eve::rem(eve::Mone<Type>()  , Value{2}), Type(-1));
    TTS_EQUAL(eve::rem(Type(-4)  , Type{3} ), Type(-1));
    TTS_EQUAL(eve::rem(Value(-4) , Type{3} ), Type(-1));
    TTS_EQUAL(eve::rem(Type(-4)  , Value{3}), Type(-1));
  }
  TTS_EQUAL(eve::rem(Type{12}, Type{4}), Type{0});
  TTS_EQUAL(eve::rem(Type{1} , Type{2}), Type(1));
  TTS_EQUAL(eve::rem(Type{4} , Type{3}), Type(1));

  TTS_EQUAL(eve::rem(Value{12}, Type{4}), Type{0});
  TTS_EQUAL(eve::rem(Value{1} , Type{2}), Type(1));
  TTS_EQUAL(eve::rem(Value{4} , Type{3}), Type(1));

  TTS_EQUAL(eve::rem(Type{12}, Value{4}), Type{0});
  TTS_EQUAL(eve::rem(Type{1} , Value{2}), Type(1));
  TTS_EQUAL(eve::rem(Type{4} , Value{3}), Type(1));
}
