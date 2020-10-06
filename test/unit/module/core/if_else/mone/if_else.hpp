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
#include <eve/constant/mone.hpp>

TTS_CASE("Check eve::if_else return type")
{
  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , EVE_TYPE(), eve::mone), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , EVE_TYPE(), eve::mone), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , EVE_TYPE(), eve::mone), EVE_TYPE);

  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , eve::mone, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , eve::mone, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , eve::mone, EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::if_else(., ., mone_) behavior ")
{
  auto f = EVE_TYPE(-1);
  auto t = EVE_TYPE(9);

  TTS_IEEE_EQUAL(eve::if_else(1                 , t, eve::mone), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , t, eve::mone), t);
  TTS_IEEE_EQUAL(eve::if_else(true              , t, eve::mone), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())    , t, eve::mone), t);
  TTS_IEEE_EQUAL(eve::if_else(0                 , t, eve::mone), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , t, eve::mone), f);
  TTS_IEEE_EQUAL(eve::if_else(false             , t, eve::mone), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())   , t, eve::mone), f);

  TTS_IEEE_EQUAL(eve::if_else(1                 , eve::mone, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , eve::mone, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true              , eve::mone, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())    , eve::mone, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0                 , eve::mone, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , eve::mone, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false             , eve::mone, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())   , eve::mone, t), t);
}
