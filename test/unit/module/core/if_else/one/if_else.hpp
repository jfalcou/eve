//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/one.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::if_else return type")
{
  TTS_EXPR_IS(eve::if_else(Type()               , Type(), eve::one_), (Type));
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>() , Type(), eve::one_), (Type));
  TTS_EXPR_IS(eve::if_else(true                 , Type(), eve::one_), (Type));

  TTS_EXPR_IS(eve::if_else(Type()               , eve::one_, Type()), (Type));
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>() , eve::one_, Type()), (Type));
  TTS_EXPR_IS(eve::if_else(true                 , eve::one_, Type()), (Type));
}

TTS_CASE("Check eve::if_else(., ., one_) behavior ")
{
  auto f = Type(1);
  auto t = Type(9);

  TTS_IEEE_EQUAL(eve::if_else(1                 , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(true              , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<Type>() , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(0                 , t, eve::one_), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , t, eve::one_), f);
  TTS_IEEE_EQUAL(eve::if_else(false             , t, eve::one_), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<Type>(), t, eve::one_), f);

  TTS_IEEE_EQUAL(eve::if_else(1                 , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true              , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<Type>() , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0                 , eve::one_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , eve::one_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false             , eve::one_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<Type>(), eve::one_, t), t);
}
