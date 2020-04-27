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
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::if_else(T()               , T(), eve::zero_), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , T(), eve::zero_), T);
  TTS_EXPR_IS(eve::if_else(true                 , T(), eve::zero_), T);

  TTS_EXPR_IS(eve::if_else(T()               , eve::zero_, T()), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , eve::zero_, T()), T);
  TTS_EXPR_IS(eve::if_else(true                 , eve::zero_, T()), T);
}

TTS_CASE_TPL("Check eve::if_else(., ., zero_) behavior ", EVE_TYPE)
{
  auto f = T(0);
  auto t = T(1);

  TTS_EQUAL(eve::if_else(1                  , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(1.0                , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(true               , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(eve::True<T>()  , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(t                  , t, eve::zero_), t);
  TTS_EQUAL(eve::if_else(0                  , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(0.0                , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(false              , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(eve::False<T>() , t, eve::zero_), f);
  TTS_EQUAL(eve::if_else(f                  , t, eve::zero_), f);

  TTS_EQUAL(eve::if_else(1                  , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(1.0                , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(true               , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(eve::True<T>()  , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(t                  , eve::zero_, t), f);
  TTS_EQUAL(eve::if_else(0                  , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(0.0                , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(false              , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(eve::False<T>() , eve::zero_, t), t);
  TTS_EQUAL(eve::if_else(f                  , eve::zero_, t), t);
}
