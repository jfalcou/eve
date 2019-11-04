//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/sub.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE("Check eve::sub return type")
{
  TTS_EXPR_IS(eve::sub(Type(), Type()), (Type));
}

TTS_CASE("Check eve::sub behavior")
{
  TTS_EQUAL(eve::sub(Type{0}, Type{0}), Type(0));
  TTS_EQUAL(eve::sub(Type{1}, Type{1}), Type(0));
  TTS_EQUAL(eve::sub(Type{6}, Type{2}), Type(4));

  TTS_EQUAL(eve::sub(Value{0}, Type{0}), Type(0));
  TTS_EQUAL(eve::sub(Value{1}, Type{1}), Type(0));
  TTS_EQUAL(eve::sub(Value{6}, Type{2}), Type(4));

  TTS_EQUAL(eve::sub(Type{0}, Value{0}), Type(0));
  TTS_EQUAL(eve::sub(Type{1}, Value{1}), Type(0));
  TTS_EQUAL(eve::sub(Type{6}, Value{2}), Type(4));

  if constexpr(std::is_signed_v<Value>)
  {
    TTS_EQUAL(eve::sub(Type(-1), Type(1)), Type(-2));
    TTS_EQUAL(eve::sub(Type(-2), Type(-6)), Type(4));

    TTS_EQUAL(eve::sub(Value(-1), Type(1)), Type(-2));
    TTS_EQUAL(eve::sub(Value(-2), Type(-6)), Type(4));

    TTS_EQUAL(eve::sub(Type(-1), Value(1)), Type(-2));
    TTS_EQUAL(eve::sub(Type(-2), Value(-6)), Type(4));
  }
}
