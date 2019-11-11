//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/clamp.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::clamp return type")
{
  TTS_EXPR_IS(eve::clamp(Type(), Type() , Type()) , (Type));
  TTS_EXPR_IS(eve::clamp(Type(), Value(), Type()) , (Type));
  TTS_EXPR_IS(eve::clamp(Type(), Type() , Value()), (Type));
  TTS_EXPR_IS(eve::clamp(Type(), Value(), Value()), (Type));
}

TTS_CASE("Check eve::clamp behavior")
{
  TTS_EQUAL(eve::clamp(Type(1), Type(2) , Type(4))  , Type(2));
  TTS_EQUAL(eve::clamp(Type(1), Value(2), Type(4))  , Type(2));
  TTS_EQUAL(eve::clamp(Type(1), Type(2) , Value(4)) , Type(2));
  TTS_EQUAL(eve::clamp(Type(1), Value(2), Value(4)) , Type(2));

  TTS_EQUAL(eve::clamp(Type(2), Type(2), Type(4)), Type(2));
  TTS_EQUAL(eve::clamp(Type(2), Value(2), Type(4)), Type(2));
  TTS_EQUAL(eve::clamp(Type(2), Type(2), Value(4)), Type(2));
  TTS_EQUAL(eve::clamp(Type(2), Value(2), Value(4)), Type(2));

  TTS_EQUAL(eve::clamp(Type(3), Type(2), Type(4)), Type(3));
  TTS_EQUAL(eve::clamp(Type(3), Value(2), Type(4)), Type(3));
  TTS_EQUAL(eve::clamp(Type(3), Type(2), Value(4)), Type(3));
  TTS_EQUAL(eve::clamp(Type(3), Value(2), Value(4)), Type(3));

  TTS_EQUAL(eve::clamp(Type(4), Type(2), Type(4)), Type(4));
  TTS_EQUAL(eve::clamp(Type(4), Value(2), Type(4)), Type(4));
  TTS_EQUAL(eve::clamp(Type(4), Type(2), Value(4)), Type(4));
  TTS_EQUAL(eve::clamp(Type(4), Value(2), Value(4)), Type(4));

  TTS_EQUAL(eve::clamp(Type(5), Type(2), Type(4)), Type(4));
  TTS_EQUAL(eve::clamp(Type(5), Value(2), Type(4)), Type(4));
  TTS_EQUAL(eve::clamp(Type(5), Type(2), Value(4)), Type(4));
  TTS_EQUAL(eve::clamp(Type(5), Value(2), Value(4)), Type(4));
}
