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

TTS_CASE("Check eve::if_else return type")
{
  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , EVE_TYPE(), eve::allbits), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , EVE_TYPE(), eve::allbits), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , EVE_TYPE(), eve::allbits), EVE_TYPE);

  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , eve::allbits, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , eve::allbits, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , eve::allbits, EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::if_else(., ., allbits) behavior ")
{
  auto f = eve::allbits(eve::as<EVE_TYPE>());
  auto t = EVE_TYPE(9);

  TTS_IEEE_EQUAL(eve::if_else(1                 , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(true              , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())    , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(0                 , t, eve::allbits), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , t, eve::allbits), f);
  TTS_IEEE_EQUAL(eve::if_else(false             , t, eve::allbits), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())   , t, eve::allbits), f);

  TTS_IEEE_EQUAL(eve::if_else(1                 , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true              , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())    , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0                 , eve::allbits, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , eve::allbits, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false             , eve::allbits, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())   , eve::allbits, t), t);
}
