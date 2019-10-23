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
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::if_else return type")
{
  TTS_EXPR_IS(eve::if_else(Type()               , Type(), eve::zero_), (Type));
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>() , Type(), eve::zero_), (Type));
  TTS_EXPR_IS(eve::if_else(true                 , Type(), eve::zero_), (Type));

  TTS_EXPR_IS(eve::if_else(Type()               , eve::zero_, Type()), (Type));
  TTS_EXPR_IS(eve::if_else(eve::logical<Type>() , eve::zero_, Type()), (Type));
  TTS_EXPR_IS(eve::if_else(true                 , eve::zero_, Type()), (Type));
}

TTS_CASE("Check eve::if_else(., ., zero_) behavior ")
{
  auto f = Type(0);
  auto t = Type(1);

  TTS_EQUAL(eve::if_else(1                  , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(1.0                , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(true               , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(eve::True<Type>()  , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(t                  , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(0                  , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(0.0                , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(false              , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(eve::False<Type>() , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(f                  , t, eve::zero_), f);

  TTS_EQUAL(eve::if_else(1                  , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(1.0                , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(true               , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(eve::True<Type>()  , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(t                  , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(0                  , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(0.0                , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(false              , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(eve::False<Type>() , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(f                  , eve::zero_, t), t);
}
