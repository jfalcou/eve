//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::if_else(T()               , T(), eve::zero), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , T(), eve::zero), T);
  TTS_EXPR_IS(eve::if_else(true              , T(), eve::zero), T);

  TTS_EXPR_IS(eve::if_else(T()               , eve::zero, T()), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , eve::zero, T()), T);
  TTS_EXPR_IS(eve::if_else(true               , eve::zero, T()), T);
}

TTS_CASE_TPL("Check eve::if_else(., ., zero_) behavior ", EVE_TYPE)
{
  auto f = T(0);
  auto t = T(1);

  TTS_EQUAL(eve::if_else(1                  , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(1.0                , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(true               , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<T>())     , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(t                  , t, eve::zero), t);
  TTS_EQUAL(eve::if_else(0                  , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(0.0                , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(false              , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<T>())    , t, eve::zero), f);
  TTS_EQUAL(eve::if_else(f                  , t, eve::zero), f);

  TTS_EQUAL(eve::if_else(1                  , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(1.0                , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(true               , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(eve::true_(eve::as<T>())     , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(t                  , eve::zero, t), f);
  TTS_EQUAL(eve::if_else(0                  , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(0.0                , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(false              , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(eve::false_(eve::as<T>())    , eve::zero, t), t);
  TTS_EQUAL(eve::if_else(f                  , eve::zero, t), t);
}
