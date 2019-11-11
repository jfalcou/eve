//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/max.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::max return type")
{
  TTS_EXPR_IS(eve::max(Type(0)  , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::max(Value(0) , Type(0) ) , (Type));
  TTS_EXPR_IS(eve::max(Type(0)  , Value(0)) , (Type));
}

TTS_CASE("Check eve::max behavior")
{
  TTS_EQUAL(eve::max((Type(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::max((Type(0)), (Type(1))), (Type(1)));
  TTS_EQUAL(eve::max((Type(1)), (Type(0))), (Type(1)));
  TTS_EQUAL(eve::max((Type(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::max((Value(0)), (Type(0))), (Type(0)));
  TTS_EQUAL(eve::max((Value(0)), (Type(1))), (Type(1)));
  TTS_EQUAL(eve::max((Value(1)), (Type(0))), (Type(1)));
  TTS_EQUAL(eve::max((Value(1)), (Type(1))), (Type(1)));

  TTS_EQUAL(eve::max((Type(0)), (Value(0))), (Type(0)));
  TTS_EQUAL(eve::max((Type(0)), (Value(1))), (Type(1)));
  TTS_EQUAL(eve::max((Type(1)), (Value(0))), (Type(1)));
  TTS_EQUAL(eve::max((Type(1)), (Value(1))), (Type(1)));
}
