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
#include <eve/constant/one.hpp>

TTS_CASE("Check eve::if_else return type")
{
  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , EVE_TYPE(), eve::one), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , EVE_TYPE(), eve::one), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , EVE_TYPE(), eve::one), EVE_TYPE);

  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , eve::one, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , eve::one, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , eve::one, EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::if_else(., ., one_) behavior ")
{
  auto f = EVE_TYPE(1);
  auto t = EVE_TYPE(9);

  TTS_EQUAL(eve::if_else(1                 , t, eve::one), t);
  TTS_EQUAL(eve::if_else(1.0               , t, eve::one), t);
  TTS_EQUAL(eve::if_else(true              , t, eve::one), t);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())    , t, eve::one), t);
  TTS_EQUAL(eve::if_else(0                 , t, eve::one), f);
  TTS_EQUAL(eve::if_else(0.0               , t, eve::one), f);
  TTS_EQUAL(eve::if_else(false             , t, eve::one), f);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())   , t, eve::one), f);

  TTS_EQUAL(eve::if_else(1                 , eve::one, t), f);
  TTS_EQUAL(eve::if_else(1.0               , eve::one, t), f);
  TTS_EQUAL(eve::if_else(true              , eve::one, t), f);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())    , eve::one, t), f);
  TTS_EQUAL(eve::if_else(0                 , eve::one, t), t);
  TTS_EQUAL(eve::if_else(0.0               , eve::one, t), t);
  TTS_EQUAL(eve::if_else(false             , eve::one, t), t);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())   , eve::one, t), t);
}
