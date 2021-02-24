//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/allbits.hpp>

TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::if_else(T()               , T(), eve::allbits), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , T(), eve::allbits), T);
  TTS_EXPR_IS(eve::if_else(true              , T(), eve::allbits), T);

  TTS_EXPR_IS(eve::if_else(T()               , eve::allbits, T()), T);
  TTS_EXPR_IS(eve::if_else(eve::logical<T>() , eve::allbits, T()), T);
  TTS_EXPR_IS(eve::if_else(true              , eve::allbits, T()), T);
}

TTS_CASE_TPL("Check eve::if_else(., ., allbits) behavior ", EVE_TYPE)
{
  auto f = eve::allbits(eve::as<T>());
  auto t = T(9);

  TTS_IEEE_EQUAL(eve::if_else(1                 , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(true              , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::true_(eve::as<T>())    , t, eve::allbits), t);
  TTS_IEEE_EQUAL(eve::if_else(0                 , t, eve::allbits), f);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , t, eve::allbits), f);
  TTS_IEEE_EQUAL(eve::if_else(false             , t, eve::allbits), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::false_(eve::as<T>())   , t, eve::allbits), f);

  TTS_IEEE_EQUAL(eve::if_else(1                 , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(1.0               , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(true              , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(eve::true_(eve::as<T>())    , eve::allbits, t), f);
  TTS_IEEE_EQUAL(eve::if_else(0                 , eve::allbits, t), t);
  TTS_IEEE_EQUAL(eve::if_else(0.0               , eve::allbits, t), t);
  TTS_IEEE_EQUAL(eve::if_else(false             , eve::allbits, t), t);
  TTS_IEEE_EQUAL(eve::if_else(eve::false_(eve::as<T>())   , eve::allbits, t), t);
}
