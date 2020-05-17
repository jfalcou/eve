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
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::if_else(T()               , T(), eve::mone_), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , T(), eve::mone_), T);
  TTS_EXPR_IS(eve::if_else(true              , T(), eve::mone_), T);

  TTS_EXPR_IS(eve::if_else(T()               , eve::mone_, T()), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , eve::mone_, T()), T);
  TTS_EXPR_IS(eve::if_else(true              , eve::mone_, T()), T);
}

TTS_CASE_TPL("Check eve::if_else(., ., mone_) behavior ", EVE_TYPE)
{
  auto f = T(-1);
  auto t = T(9);

  TTS_IEEE_EQUAL(eve::if_else(1                 , t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(true              , t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<T>()    , t, eve::mone_), t);
  TTS_IEEE_EQUAL(eve::if_else(0                 , t, eve::mone_), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , t, eve::mone_), f);
  TTS_IEEE_EQUAL(eve::if_else(false             , t, eve::mone_), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<T>()   , t, eve::mone_), f);

  TTS_IEEE_EQUAL(eve::if_else(1                 , eve::mone_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , eve::mone_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true              , eve::mone_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::True<T>()    , eve::mone_, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0                 , eve::mone_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , eve::mone_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false             , eve::mone_, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::False<T>()   , eve::mone_, t), t);
}
