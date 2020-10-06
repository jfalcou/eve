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
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

TTS_CASE("Check eve::if_else return type")
{
  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , EVE_TYPE(), eve::zero), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , EVE_TYPE(), eve::zero), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , EVE_TYPE(), eve::zero), EVE_TYPE);

  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , eve::zero, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , eve::zero, EVE_TYPE()), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                      , eve::zero, EVE_TYPE()), EVE_TYPE);
}

TTS_CASE("Check eve::if_else(., ., zero_) behavior ")
{
  auto f = EVE_TYPE(0);
  auto t = EVE_TYPE(1);

  TTS_EQUAL(eve::if_else(1                  , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(1.0                , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(true               , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())     , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(t                  , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(0                  , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(0.0                , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(false              , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())    , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(f                  , t, eve::zero), f);

  TTS_EQUAL(eve::if_else(1                  , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(1.0                , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(true               , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<EVE_TYPE>())     , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(t                  , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(0                  , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(0.0                , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(false              , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<EVE_TYPE>())    , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(f                  , eve::zero, t), t);
}
