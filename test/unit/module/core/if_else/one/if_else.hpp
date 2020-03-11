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
  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , EVE_TYPE(), eve::one_), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , EVE_TYPE(), eve::one_), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(true                 , EVE_TYPE(), eve::one_), (EVE_TYPE));

  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , eve::one_, EVE_TYPE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , eve::one_, EVE_TYPE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(true                 , eve::one_, EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::if_else(., ., one_) behavior ")
{
  auto f = EVE_TYPE(1);
  auto t = EVE_TYPE(9);

  TTS_IEEE_EQUAL(eve::if_else(1                 , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(true              , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<EVE_TYPE>() , t, eve::one_), t);
  TTS_IEEE_EQUAL(eve::if_else(0                 , t, eve::one_), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , t, eve::one_), f);
  TTS_IEEE_EQUAL(eve::if_else(false             , t, eve::one_), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<EVE_TYPE>(), t, eve::one_), f);

  TTS_IEEE_EQUAL(eve::if_else(1                 , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true              , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<EVE_TYPE>() , eve::one_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0                 , eve::one_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , eve::one_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false             , eve::one_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<EVE_TYPE>(), eve::one_, t), t);
}
