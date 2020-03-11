//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/allbits.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE("Check eve::if_else return type")
{
  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , EVE_TYPE(), eve::allbits_), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , EVE_TYPE(), eve::allbits_), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(true                 , EVE_TYPE(), eve::allbits_), (EVE_TYPE));

  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , eve::allbits_, EVE_TYPE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , eve::allbits_, EVE_TYPE()), (EVE_TYPE));
  TTS_EXPR_IS(eve::if_else(true                 , eve::allbits_, EVE_TYPE()), (EVE_TYPE));
}

TTS_CASE("Check eve::if_else(., ., allbits_) behavior ")
{
  auto f = eve::Allbits<EVE_TYPE>();
  auto t = EVE_TYPE(9);

  TTS_IEEE_EQUAL(eve::if_else(1                 , t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(true              , t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<EVE_TYPE>() , t, eve::allbits_), t);
  TTS_IEEE_EQUAL(eve::if_else(0                 , t, eve::allbits_), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , t, eve::allbits_), f);
  TTS_IEEE_EQUAL(eve::if_else(false             , t, eve::allbits_), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<EVE_TYPE>(), t, eve::allbits_), f);

  TTS_IEEE_EQUAL(eve::if_else(1                 , eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true              , eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<EVE_TYPE>() , eve::allbits_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0                 , eve::allbits_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , eve::allbits_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false             , eve::allbits_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<EVE_TYPE>(), eve::allbits_, t), t);
}
