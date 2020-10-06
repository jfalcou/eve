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
  TTS_EXPR_IS(eve::if_else(EVE_TYPE()               , EVE_TYPE(), EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS( eve::if_else(eve::logical<EVE_TYPE>(), EVE_TYPE(), EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(true                     , EVE_TYPE(), EVE_TYPE()  ), EVE_TYPE);
  TTS_EXPR_IS(eve::if_else(eve::logical<EVE_TYPE>() , EVE_TYPE(), EVE_VALUE() ), EVE_TYPE);
}

TTS_CASE("Check eve::if_else behavior with arithmetic alternatives")
{
  EVE_TYPE tv{2};
  EVE_TYPE fv{3};
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());

  TTS_EQUAL(eve::if_else(1    , tv, fv), tv);
  TTS_EQUAL(eve::if_else(1.0  , tv, fv), tv);
  TTS_EQUAL(eve::if_else(true , tv, fv), tv);
  TTS_EQUAL(eve::if_else(t    , tv, fv), tv);
  TTS_EQUAL(eve::if_else(0    , tv, fv), fv);
  TTS_EQUAL(eve::if_else(0.0  , tv, fv), fv);
  TTS_EQUAL(eve::if_else(false, tv, fv), fv);
  TTS_EQUAL(eve::if_else(f    , tv, fv), fv);
  TTS_EQUAL(eve::if_else(fv    , tv, fv), tv);
}

TTS_CASE("Check eve::if_else behavior with logical alternatives")
{
  auto t = eve::true_(eve::as<EVE_TYPE>());
  auto f = eve::false_(eve::as<EVE_TYPE>());
  EVE_TYPE fv{3};

  TTS_EQUAL(eve::if_else(1    , t, f), t);
  TTS_EQUAL(eve::if_else(1.0  , t, f), t);
  TTS_EQUAL(eve::if_else(true , t, f), t);
  TTS_EQUAL(eve::if_else(t    , t, f), t);
  TTS_EQUAL(eve::if_else(0    , t, f), f);
  TTS_EQUAL(eve::if_else(0.0  , t, f), f);
  TTS_EQUAL(eve::if_else(false, t, f), f);
  TTS_EQUAL(eve::if_else(f    , t, f), f);
  TTS_EQUAL(eve::if_else(fv   , t, f), t);
}
