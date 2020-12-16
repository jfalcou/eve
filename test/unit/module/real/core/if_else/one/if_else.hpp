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

TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::if_else(T()               , T(), eve::one), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , T(), eve::one), T);
  TTS_EXPR_IS(eve::if_else(true              , T(), eve::one), T);

  TTS_EXPR_IS(eve::if_else(T()               , eve::one, T()), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , eve::one, T()), T);
  TTS_EXPR_IS(eve::if_else(true              , eve::one, T()), T);
}

TTS_CASE_TPL("Check eve::if_else(., ., one_) behavior ", EVE_TYPE)
{
  auto f = T(1);
  auto t = T(9);

  TTS_EQUAL(eve::if_else(1                 , t, eve::one), t);
  TTS_EQUAL(eve::if_else(1.0               , t, eve::one), t);
  TTS_EQUAL(eve::if_else(true              , t, eve::one), t);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<T>())    , t, eve::one), t);
  TTS_EQUAL(eve::if_else(0                 , t, eve::one), f);
  TTS_EQUAL(eve::if_else(0.0               , t, eve::one), f);
  TTS_EQUAL(eve::if_else(false             , t, eve::one), f);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<T>())   , t, eve::one), f);

  TTS_EQUAL(eve::if_else(1                 , eve::one, t), f);
  TTS_EQUAL(eve::if_else(1.0               , eve::one, t), f);
  TTS_EQUAL(eve::if_else(true              , eve::one, t), f);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<T>())    , eve::one, t), f);
  TTS_EQUAL(eve::if_else(0                 , eve::one, t), t);
  TTS_EQUAL(eve::if_else(0.0               , eve::one, t), t);
  TTS_EQUAL(eve::if_else(false             , eve::one, t), t);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<T>())   , eve::one, t), t);
}
